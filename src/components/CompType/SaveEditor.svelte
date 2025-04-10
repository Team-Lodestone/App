<script lang="ts">
  import CompType from '../CompType.svelte'
  import { navigate } from 'svelte5-router'
  import {
    type InnerFileType,
    type platforms,
    type search,
    type compressionMethods
  } from '../../types'
  import { SaveFileEditorParamStore } from '../../store.js'
  import { loadingScreen, onFilesChosen } from '../../main'
  import { SlideUp, FSPickerButton, DropDownBox } from '@team-lodestone/lodestone-ui'

  /* Goals
   *
   * - Clean up
   * - Make file scanning more versatile (e.g something where we can easily add regex/names, etc)
   * - JE and BE support (after LCE works)
   */

  let selectedEdition = 'Java'
  let byteOrder: string = '0'
  let platform: platforms = 'Xbox 360'
  let thumbNameSize: number = 0
  let compression: compressionMethods = 'LZX'
  let hasChosen: boolean = false

  let fileNames = new Map<platforms, InnerFileType>([
    ['Xbox 360', { savegame: { type: 'str', value: 'savegame.dat' } }],
    [
      'Xbox One',
      {
        savegame: { type: 'str', value: 'GAMEDATA' },
        thumb: { type: 'str', value: 'THUMB' },
        region: { type: 'regex', value: /^(GAMEDATA)_(\d{4})([0-9a-fA-F]{2})([0-9a-fA-F]{2})$/ }
      }
    ],
    [
      'PS3',
      {
        savegame: { type: 'str', value: 'GAMEDATA' },
        thumb: { type: 'str', value: 'THUMB' },
        metadata: { type: 'str', value: 'METADATA' }
      }
    ],
    [
      'PSVita',
      {
        savegame: { type: 'str', value: 'GAMEDATA.bin' },
        thumb: { type: 'str', value: 'THUMBDATA.bin' }
      }
    ],
    [
      'PS4',
      {
        savegame: { type: 'str', value: 'GAMEDATA' },
        thumb: { type: 'str', value: 'THUMB' },
        region: { type: 'regex', value: /^(GAMEDATA)_(\d{4})([0-9a-fA-F]{2})([0-9a-fA-F]{2})$/ }
      }
    ],
    [
      'Wii U',
      {
        savegame: { type: 'regex', value: /^\d{12,}(?!.ext)/ },
        thumb: { type: 'regex', value: /\d{12,}\.ext/ },
        settings: { save_must_match_thumb_filename: true, thumb_ext_size: 4 }
      }
    ],
    [
      'Nintendo Switch',
      {
        savegame: { type: 'regex', value: /^\d{12,}\.dat/ },
        thumb: { type: 'regex', value: /^\d{12,}\.ext/ },
        region: { type: 'regex', value: /^(GAMEDATA)_(\d{4})([0-9a-fA-F]{2})([0-9a-fA-F]{2})$/ }
      }
    ]
  ])

  let editButton: HTMLButtonElement

  let saveFileComp: CompType

  let regions: File[] = []
  let unknownFiles: File[] = []
  let saveFile: File
  let thumb: File
  let metadata: File

  function switchEdition(edition: string): void {
    selectedEdition = edition
  }

  const getFilesCount = (): number => {
    let ret = 0

    if (saveFile) ret++
    if (thumb) ret++
    if (metadata) ret++
    ret += regions.length
    ret += unknownFiles.length

    return ret
  }

  // TODO: add multiple save choosing incase user opens folder with multiple saves.
  const onSaveFilesChosen = (event): void => {
    console.log(event)

    saveFile = undefined
    thumb = undefined
    metadata = undefined
    regions = []

    hasChosen = true
    const files = onFilesChosen(event)
    getFiles(files)
  }

  // shitty way to see what the file is by checking the name
  function getFiles(files: FileList): void {
    const names = fileNames.get(platform)

    for (const f of files) {
      let hasGottenType = false

      if (names.savegame) {
        const sg = names.savegame.value
        if (sg && !saveFile) {
          if (sg instanceof RegExp) {
            if (sg.test(f.name)) {
              saveFile = f
              hasGottenType = true
            }
          } else {
            if (f.name === sg) {
              saveFile = f
              hasGottenType = true
            }
          }
        }
      }

      if (names.region) {
        const dim = names.region.value
        if (dim) {
          if (dim instanceof RegExp) {
            if (dim.test(f.name)) {
              regions.push(f)
              hasGottenType = true
            }
          } else {
            if (f.name === dim) {
              regions.push(f)
              hasGottenType = true
            }
          }
        }
      }

      if (names.thumb) {
        const th = names.thumb.value
        if (th && !thumb) {
          if (th instanceof RegExp) {
            if (th.test(f.name)) {
              thumb = f
              hasGottenType = true
            }
          } else {
            if (f.name === th) {
              thumb = f
              hasGottenType = true
            }
          }
        }
      }

      if (names.metadata) {
        const md = names.metadata.value
        if (md && !metadata) {
          if (md instanceof RegExp) {
            if (md.test(f.name)) {
              metadata = f
              hasGottenType = true
            }
          } else {
            if (f.name === md) {
              metadata = f
              hasGottenType = true
            }
          }
        }
      }

      if (!hasGottenType) {
        unknownFiles.push(f)
      }
    }

    if (names.settings && names.settings.save_must_match_thumb_filename) {
      const list: Array<File> = Array.from(files)

      let th = thumb.name
      if (names.settings.thumb_ext_size !== 0)
        th = th.substring(0, th.length - names.settings.thumb_ext_size)

      const match = list.find((f) => f.name.includes(th))
      if (match) {
        saveFile = match
      }
    }

    if (saveFile) console.log(`Chose ${saveFile.name} as Savegame`)
    if (thumb) console.log(`Chose ${thumb.name} as Thumb`)
    regions = [...regions]
    unknownFiles = [...unknownFiles]

    editButton.disabled = !(saveFile || thumb || regions.length === 0)
  }

  // TODO: map
  const onPlatformChosen = (event): void => {
    switch (platform) {
      case 'Xbox 360':
        byteOrder = '0'
        compression = 'LZX'
        thumbNameSize = 0
        break
      case 'Nintendo Switch':
        byteOrder = '1'
        compression = 'Zlib'
        thumbNameSize = 0x208
        break
      case 'PS4':
      case 'Xbox One':
        byteOrder = '1'
        compression = 'Zlib'
        thumbNameSize = 0
        break
      case 'PS3':
        byteOrder = '0'
        compression = 'Deflate'
        thumbNameSize = 0
        break
      case 'Wii U':
        byteOrder = '0'
        compression = 'Zlib'
        thumbNameSize = 0x100
        break
      case 'PSVita':
        byteOrder = '1'
        compression = 'Vita RLE'
        thumbNameSize = 0
        break
    }
  }

  const onSaveEditing = async (): Promise<void> => {
    console.log(byteOrder)
    loadingScreen.shown = true
    loadingScreen.title = 'Loading file'
    saveFileComp.toggleOptions()
    SaveFileEditorParamStore.set({
      endian: parseInt(byteOrder),
      compression,
      file: saveFile,
      platform: platform,
      thumbnail: thumb,
      thumbnailNameSize: thumbNameSize,
      regions,
      unknownFiles
    })
    navigate('/SaveFileEditor')
  }
</script>

<CompType bind:this={saveFileComp} name="Save Editor">
  <div class="editionButtons">
    <!-- eslint-disable-next-line @typescript-eslint/explicit-function-return-type -->
    <button style="border-radius:0;" class="editionButton" on:click={() => switchEdition('Java')}
      >Java Edition</button
    >
    <!-- eslint-disable-next-line @typescript-eslint/explicit-function-return-type -->
    <button style="border-radius:0;" class="editionButton" on:click={() => switchEdition('Bedrock')}
      >Bedrock Edition</button
    >
    <!-- eslint-disable-next-line @typescript-eslint/explicit-function-return-type -->
    <button style="border-radius:0;" class="editionButton" on:click={() => switchEdition('LCE')}
      >Legacy Console Edition</button
    >
  </div>
  <div
    style="display:flex;flex-direction:column;align-content: center;align-items: center;justify-content: center;gap: 10px;"
  >
    {#if selectedEdition === 'LCE'}
      <DropDownBox
        header="Platform"
        tooltip="The console your save was made on"
        bind:value={platform}
        selectionChange={onPlatformChosen}
      >
        <option>Xbox 360</option>
        <option>Xbox One</option>
        <option>PS3</option>
        <option>PSVita</option>
        <option>PS4</option>
        <option>Wii U</option>
        <option>Nintendo Switch</option>
      </DropDownBox>

      <div
        style="display:flex;flex-direction:row;align-content: center;align-items: center;align-self:center;justify-content: center;gap:20px;"
      >
        <FSPickerButton
          title="Choose save file(s)"
          moreInfo=""
          onChosen={onSaveFilesChosen}
          multiple
        ></FSPickerButton>
        <FSPickerButton title="Choose a save folder" onChosen={onSaveFilesChosen} folder
        ></FSPickerButton>
      </div>
    {/if}
    {#if selectedEdition === 'Java' || selectedEdition === 'Bedrock'}
      <h1>Support for this edition has not been added yet.</h1>
    {/if}
  </div>
  <div style="margin-top: 10px;display:flex;flex-direction:column;">
    {#if selectedEdition === 'LCE'}
      {#if hasChosen}
        <SlideUp title="Files ({getFilesCount()})">
          <div style="display:flex;flex-direction:column;gap:5px;overflow-y:auto;max-height:5%;">
            {#if saveFile !== undefined}
              <div class="sfFile save">
                {saveFile.name}
                <div class="save">Save</div>
              </div>
            {/if}
            {#if thumb !== undefined}
              <div
                class="sfFile thumb"
                title="The thumbnail file (often named THUMB) contains information about your world such as: The world name (depending on console), The seed, Save image (the screenshot of your logoff point), Host options, etc."
              >
                {thumb.name}
                <div class="thumb">Thumbnail</div>
              </div>
            {/if}
            {#if metadata !== undefined}
              <div class="sfFile meta">
                {metadata.name}
                <div class="meta">Metadata</div>
              </div>
            {/if}
            {#if regions.length > 0}
              {#each regions as region}
                <div class="sfFile">
                  {region.name}
                  <div class="region">Region</div>
                </div>
              {/each}
            {/if}
            {#if unknownFiles.length > 0}
              {#each unknownFiles as unk}
                <div class="sfFile">
                  {unk.name}
                  <DropDownBox
                    class="unknownFile"
                    value="Unknown"
                    tooltip="Change file type"
                    selectionChange={(e) => {
                      // broken kinda
                      switch (e.target.value) {
                        case 'Region':
                          regions.push(unk)
                          regions = [...regions]
                          break
                        case 'Save':
                          saveFile = unk
                          break
                        case 'Thumbnail':
                          thumb = unk
                          break
                        case 'Metadata':
                          metadata = unk
                          break
                        case 'Unknown':
                        default:
                          return
                      }
                      unknownFiles.filter((item) => item !== unk)
                      unknownFiles = [...unknownFiles]
                    }}
                  >
                    <option>Save</option>
                    <option>Thumbnail</option>
                    <option>Metadata</option>
                    <option>Region</option>
                    <option>Unknown</option>
                  </DropDownBox>
                </div>
              {/each}
            {/if}
          </div>
        </SlideUp>
      {/if}
      <SlideUp title="Advanced options">
        <DropDownBox header="Byte Order" bind:value={byteOrder}>
          <option value="0">Big</option>
          <option value="1">Little</option>
        </DropDownBox>
        <DropDownBox header="Compression" bind:value={compression}>
          <option>None</option>
          <option>LZX</option>
          <option>Zlib</option>
          <option>Deflate</option>
          <option>Vita RLE</option>
        </DropDownBox>
      </SlideUp>
    {/if}
    <button style="border-radius:0;" on:click={onSaveEditing} bind:this={editButton} disabled
      >Start editing</button
    >
  </div>
</CompType>

<style>
  .sfFile {
    display: flex;
    flex-direction: row;
    padding: 5px;
    border: 1px solid var(--bg-border);
    border-radius: 5px;
    background-color: var(--bg-alt);
    width: 300px;
  }

  .sfFile .region {
    padding: 5px;
    margin-left: auto;
    border: 2px solid var(--bg-border);
    border-radius: 10px;
    background-color: cornflowerblue;
  }

  .sfFile .unknownFile {
    padding: 5px;
    margin-left: auto;
    border: 2px solid var(--bg-border);
    border-radius: 10px;
    background-color: var(--bg-alt-2);
  }

  .sfFile .save {
    padding: 5px;
    margin-left: auto;
    border: 2px solid var(--bg-border);
    border-radius: 10px;
    background-color: seagreen;
  }

  .sfFile .thumb {
    padding: 5px;
    margin-left: auto;
    border: 2px solid var(--bg-border);
    border-radius: 10px;
    background-color: indianred;
  }

  .sfFile .meta {
    padding: 5px;
    margin-left: auto;
    border: 2px solid var(--bg-border);
    border-radius: 10px;
    background-color: rebeccapurple;
  }

  .editionButton {
    width: 100%;
    border-radius: 0;
  }

  .editionButtons {
    display: flex;
    flex-direction: row;
    border-radius: 0;
  }
</style>
