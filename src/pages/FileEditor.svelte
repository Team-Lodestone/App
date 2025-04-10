<script lang="ts">
  import { type SaveFileEditorParams } from '../store'
  import Module from '../wasm/libLCE.js'
  import { loadingScreen } from '../main'
  import { navigate } from 'svelte5-router'
  import Tree from '../components/Tree.svelte'
  import SaveFileEditor from '../components/FileEditors/SaveFileEditor.svelte'
  import { fromFile, type LodestoneFile, type TreeNode } from '../Lodestone'
  import RegionEditor from '../components/FileEditors/RegionEditor.svelte'

  /* Goals
   * This should be made more general purpose if possible.
   * Universally used, I guess... if the user wants to edit say an NBT file, and they drag it in, it'll open this menu where they will be able to edit the file.
   * This means separating the Save logic completely from this, which is what I'd prefer.
   *
   * As for cleanliness, that also needs to happen... this was more of a "just get it working and clean later." initially, but it's pain to even deal with now.
   * For example, the Tree component is heavily intertwined with this... which I personally don't like.
   */

  let files: Array<LodestoneFile> = []
  export let params: SaveFileEditorParams
  let sidebar: HTMLDivElement
  let mainArea: HTMLDivElement
  let save
  let worldName: string = 'World'
  let worldImage: HTMLCanvasElement
  let currentFile: TreeNode<LodestoneFile>

  if (!params.file) {
    navigate('/')
  }

  if (!params.thumbnail || params.thumbnailNameSize === 0) {
    worldName = (params.file ?? { name: 'Unknown File' }).name
  }

  let tree: Array<TreeNode<LodestoneFile>> = []
  const handleFileClick = (f) => {
    currentFile = f
  }

  const handleExpand = (f) => {
    currentFile = f
  }

  const readSave = async (): Promise<void> => {
    const mod = await Module()

    mod.printLibraryInfo()
    if (params.file) {
      const endian = params.endian == 0 ? mod.ByteOrder.BIG : mod.ByteOrder.LITTLE

      let arrayBuf = await params.file.arrayBuffer()

      loadingScreen.progress = 10
      loadingScreen.title = 'Passing save file to libLCE'

      let uint8array = new Uint8Array(arrayBuf)
      loadingScreen.progress = 15

      let vector = mod.VectorFromUInt8Array(uint8array)
      if (params.compression !== 'None') {
        loadingScreen.title = 'Decompressing save'
        loadingScreen.progress = 20

        let size = mod.Compression.getSizeFromSave(vector, endian)
        let out = mod.VectorFromUInt8Array(new Uint8Array(size))

        console.log(out)

        switch (params.compression) {
          case 'Zlib': {
            let err = mod.Compression.decompressZlibWithLength(vector, out, size, 8)

            if (err === false) vector = out
            else throw new Error('Zlib decompression failed!')

            break
          }
          case 'Vita RLE': {
            let err = mod.Compression.decompressVita(vector, out, size, 8)
            if (err === false) vector = out
            break
          }
        }
      }

      loadingScreen.progress = 25
      loadingScreen.title = 'Reading save file'

      try {
        console.log(endian)
        let ver = mod.SaveFileCommons.getVersionFromData(vector, endian)

        // no std::variant??? :(
        if (ver > 1) {
          save = new mod.SaveFile(vector, endian)
        } else {
          save = new mod.SaveFileOld(vector, endian)
        }
      } catch (e) {
        console.error(e)
        navigate('/')
        loadingScreen.shown = false
        return
      }

      if (params.thumbnail) {
        loadingScreen.title = 'Reading thumbnail'
        loadingScreen.progress = 30

        let thumbArrayBuf = await params.thumbnail.arrayBuffer()
        loadingScreen.progress = 35

        let thumbUint8array = new Uint8Array(thumbArrayBuf)
        loadingScreen.progress = 40

        let thumbVector = mod.VectorFromUInt8Array(thumbUint8array)
        loadingScreen.progress = 45
        loadingScreen.title = 'Processing thumbnail'

        // reading specific files I think should be standalone
        try {
          let thumb = new mod.Thumb(
            thumbVector,
            endian,
            params.thumbnailNameSize,
            params.platform === 'Nintendo Switch'
          )

          if (thumb.worldName !== '') {
            worldName = thumb.worldName
          }

          let img = new Uint8Array(mod.VectorToUInt8Array(thumb.image))

          console.log(img)
          const ctx = worldImage.getContext('2d')
          const imageData = new ImageData(new Uint8ClampedArray(img), 64, 64)
          ctx.putImageData(imageData, 0, 0)
        } catch (e) {
          console.error(e)
          navigate('/')
          loadingScreen.shown = false
          return
        }
      }

      loadingScreen.title = 'Processing save file'
      loadingScreen.progress = 60

      let files: LodestoneFile[] = []

      for (let i = 0; i < save.index.size(); i++) {
        const file = save.index.get(i)
        // eslint-disable-next-line no-control-regex
        const filename: string = file.name.replace(/\u0000/g, '')
        loadingScreen.title = `Processing file ${filename}`

        let data: Uint8Array = mod.VectorToUInt8Array(file.data)

        files.push({
          name: filename,
          size: file.size,
          offset: file.offset,
          timestamp: Number(file.timestamp),
          buffer: data
        })

        loadingScreen.progress = 60 + (i / (save.index.size() - 1)) * (100 - 60)
      }

      files.forEach((file: LodestoneFile) => {
        let path = file.name.split('/')
        let currentNode: TreeNode<LodestoneFile>[] = tree

        path.forEach((part, index) => {
          let isFile = index === path.length - 1

          let node: TreeNode<LodestoneFile> = currentNode.find((node) => node.file.name === part)

          if (!node) {
            file.name = part

            // looks better than ternary hell
            if (isFile)
              node = {
                file,
                fileType: file.name.endsWith('.mcr') ? 'region' : null,
                children: [],
                type: isFile ? 'file' : 'directory'
              }
            else
              node = {
                file: { name: part, size: 0, buffer: new Uint8Array() },
                children: [],
                type: isFile ? 'file' : 'directory'
              }

            currentNode.push(node)
          }

          if (!isFile) {
            currentNode = node.children
          }
        })
      })

      let sfTree: TreeNode<LodestoneFile>[] = [
        {
          file: await fromFile(params.file),
          cppType: save,
          fileType: 'save',
          type: 'file',
          children: tree
        }
      ]

      if (params.thumbnail)
        sfTree.push({
          file: await fromFile(params.thumbnail),
          type: 'file',
          fileType: 'thumb',
          children: []
        })

      for (const region of params.regions) {
        console.log(mod.Region.getDimFromFilename(region.name))
        sfTree.push({
          file: await fromFile(region),
          type: 'file',
          fileType: 'region',
          children: []
        })
      }

      tree = [...sfTree]
    }
    loadingScreen.shown = false
  }

  readSave()
</script>

<svelte:head>
  <title>Project Lodestone | Editing {worldName}</title>
</svelte:head>

<div class="content">
  <div class="sidebar" bind:this={sidebar}>
    <div class="fileListing">
      <div class="fileListingBar">
        <p style="margin-left: 10px;">Files</p>
      </div>
      <div class="fileList">
        <Tree {tree} onClick={handleFileClick} onExpand={handleExpand} />
      </div>
    </div>
    <div class="exportOptions">
      <div class="exportBar">
        {#if params.thumbnail}
          <canvas width="64" height="64" class="worldImage" bind:this={worldImage}></canvas>
        {/if}
        <p style="margin-left: 10px;">{worldName}</p>
      </div>
    </div>
  </div>

  <div class="mainArea" bind:this={mainArea}>
    {#if currentFile}
      {#if currentFile.fileType === 'save'}
        <SaveFileEditor save={currentFile}></SaveFileEditor>
      {:else if currentFile.fileType === 'region'}
        <RegionEditor region={currentFile}></RegionEditor>
      {/if}
    {/if}
  </div>
</div>

<style>
  :root {
    transition: background-color 0.55s;
  }

  .sidebar {
    display: flex;
    flex-direction: column;
    overflow-x: hidden;
    height: 100%;
    max-height: 100%;
    grid-column: 1;
    grid-row: 1 / 2;
    background-color: var(--bg-alt-2);
  }

  .fileListing {
    display: flex;
    flex-direction: column;
    background-color: var(--bg-alt-2);
    height: 70vh;
    max-height: 70vh;
    margin: 0;
  }

  .fileList {
    overflow-y: scroll;
    height: 70vh;
    max-height: 70vh;
  }

  .fileListingBar {
    display: flex;
    flex-direction: row;
    align-items: center;
    height: 60px;
    background-color: var(--bg-alt);
    border-bottom: 3px solid var(--bg-border);
  }

  .exportOptions p {
    margin: 0;
  }

  .exportOptions {
    display: flex;
    flex-direction: column;
    height: 30vh;
    background-color: var(--bg-alt-2);
  }

  .exportBar {
    display: flex;
    flex-direction: row;
    align-items: center;
    height: 60px;
    background-color: var(--bg-alt);
    border-bottom: 3px solid var(--bg-border);
  }

  li:nth-child(odd) {
    background-color: var(--bg-alt);
  }

  :global(ul) {
    margin: 0;
  }

  li,
  ul {
    list-style-type: none;
    margin: 0;
    padding-left: 0;
  }

  .folder {
    margin-left: 5px;
  }

  .sidebar p {
    margin: 0;
  }

  .content {
    display: grid;
    grid-template-columns: 30vh 1fr;
    grid-template-rows: auto 2fr;
    grid-gap: 5px;
  }

  .mainArea {
    width: 100vw;
    grid-row: 1 / 3;
    grid-column: 2;
  }

  @media (max-height: 960px) {
    .exportBar {
      height: 80px;
    }
    .worldImage {
      width: 64px;
      height: 64px;
    }
  }

  @media (max-height: 880px) {
    .exportBar {
      height: 70px;
    }
    .worldImage {
      width: 56px;
      height: 56px;
    }
  }

  @media (max-height: 780px) {
    .worldImage {
      width: 48px;
      height: 48px;
    }
  }

  @media (max-height: 660px) {
    .worldImage {
      width: 40px;
      height: 40px;
    }
  }

  @media (max-height: 580px) {
    .worldImage {
      width: 32px;
      height: 32px;
    }
  }

  @media (max-height: 460px) {
    .worldImage {
      width: 24px;
      height: 24px;
    }
  }

  .worldImage {
    border: 2px solid var(--bg-border);
    margin-left: 5px;
  }
</style>
