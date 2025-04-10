<script lang="ts">
  import { loadingScreen, version } from '../main'
  import { Option } from '@team-lodestone/lodestone-ui'

  // maybe could make a LocalStorage class?
  // Options.ts or something

  export function getSetting(setting: string, def: string = null): string {
    if (!localStorage.getItem(setting)) localStorage.setItem(setting, def)

    return localStorage.getItem(setting)
  }

  export function setSetting(setting: string, value: string): void {
    localStorage.setItem(setting, value)
  }

  export function setSettingFromSelectElement(event: Event): void {
    const setting = (event.currentTarget as HTMLElement).dataset.setting
    localStorage.setItem(setting, (event.currentTarget as HTMLSelectElement).value)
  }

  let showPatchNotes: string = getSetting('showPatchNotes', 'true')
  let lastReadPatchNotes = getSetting('lastReadPatchNotes', version)

  function debugLoadingScreen(): void {
    loadingScreen.shown = true
    loadingScreen.title =
      'Press backspace to close, left/right arrow to increment/decrement progress.'
    loadingScreen.progress = 50
    document.addEventListener('keydown', (event) => {
      switch (event.key) {
        case 'Backspace':
          loadingScreen.shown = false
          document.removeEventListener('keydown', this)
          break
        case 'ArrowLeft':
          if (loadingScreen.progress > 0) loadingScreen.progress -= 1
          break
        case 'ArrowRight':
          if (loadingScreen.progress < 100) loadingScreen.progress += 1
          break
      }
    })
  }

  function showUpdateNotice(): void {
    localStorage.setItem('lastReadPatchNotes', '0')
  }
</script>

<svelte:head>
  <title>Project Lodestone | Settings</title>
</svelte:head>
<div class="Settings">
  <h1>UI</h1>
  <hr />
  <Option title="When to show patch notes on new update">
    <select
      data-setting="showPatchNotes"
      bind:value={showPatchNotes}
      on:change={setSettingFromSelectElement}
    >
      <option value="true">Show every update</option>
      <option value="false">Do not show</option>
    </select>
  </Option>

  <h1>Debug</h1>
  <hr />

  <Option title="Show Loading Screen">
    <button on:click={debugLoadingScreen}>Show loading screen</button>
  </Option>
  <Option title="Force show new update screen" description="Sets lastReadPatchNotes to 0.">
    <button on:click={showUpdateNotice}>Force show new update screen</button>
  </Option>
</div>

<style>
  .Settings {
    display: flex;
    flex-direction: column;
    align-items: flex-start;
    padding: 10px;
    gap: 10px;
  }
</style>
