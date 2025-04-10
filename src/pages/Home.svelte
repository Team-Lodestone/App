<script lang="ts">
  import logo from '../assets/Lodestone.svg'
  import { version } from '../main'
  import CompType from '../components/CompType.svelte'
  import SaveEditor from '../components/CompType/SaveEditor.svelte'
  import { Dialog } from '@team-lodestone/lodestone-ui'
  import FromTo from '../components/FromTo.svelte'
  import { onMount } from 'svelte'
  import { marked } from 'marked'

  let patchNotes: string = null
  marked.setOptions({
    gfm: true,
    breaks: true
  })

  let lastReadPatchNotes = localStorage.getItem('lastReadPatchNotes')
  if (!lastReadPatchNotes) {
    localStorage.setItem('lastReadPatchNotes', version)
    lastReadPatchNotes = localStorage.getItem('lastReadPatchNotes')
  }

  const setVer = (): void => {
    localStorage.setItem('lastReadPatchNotes', version)
  }

  const getPatchNotes = async (): Promise<string> => {
    const notes = await fetch(`/App/patch_notes/${version}.md`, { cache: 'no-store' })

    let contentType = notes.headers.get('content-type')

    if (contentType !== 'text/html') {
      return notes.text()
      // for some reason no svelte 5 routers will return the correct status code
    } else if (contentType === 'text/html') {
      return `Couldn't find patch notes for update ${version}.\nMaybe patch notes haven't been written yet?`
    }

    return `Couldn't get patch notes for update ${version}`
  }

  onMount(async () => {
    patchNotes = await getPatchNotes()
  })
</script>

<svelte:head>
  <title>Project Lodestone | Home</title>
</svelte:head>

{#if lastReadPatchNotes !== version}
  <Dialog title="New update" visible={true} onClose={setVer}>
    <div style="padding: 10px;">
      <h3>Welcome back! You may not have noticed, but Project Lodestone has just been updated.</h3>
      <FromTo first={lastReadPatchNotes} last={version}></FromTo>
      <h1>Patch notes</h1>
      <hr />
      <div class="patchNotes">
        {#if patchNotes}
          <!-- eslint-disable-next-line svelte/no-at-html-tags -->
          {@html marked.parse(patchNotes)}
        {/if}
      </div>
      <h3>As always, the project roadmap can be viewed in the <a href="/Documentation/readme.html#project-roadmap">Documentation</a></h3>
    </div>
  </Dialog>
{/if}

<div id="Home">
  <img alt="logo" class="logo" src={logo} />
  <div style="display: flex;flex-direction:row;gap:20px;margin-top:30px;">
    <CompType isDisabled="true" name="World Converter" />
    <SaveEditor></SaveEditor>
    <CompType isDisabled="true" name="File Editor" />
  </div>
  <p class="bottom-left">{version}</p>
  <p class="bottom-right">WORK IN PROGRESS</p>
</div>
