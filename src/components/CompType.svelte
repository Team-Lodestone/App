<script lang="ts">
  import { Dialog } from '@team-lodestone/lodestone-ui'

  export let name
  export let background = ''
  export let isDisabled = 'false'

  let dialog: Dialog

  // eslint-disable-next-line @typescript-eslint/explicit-function-return-type
  export const toggleOptions = () => {
    dialog.toggleVisibility()
  }
</script>

<Dialog bind:this={dialog} title={name} image={background}>
  <slot></slot>
</Dialog>

<button
  id="card"
  class="compCard"
  disabled={isDisabled === 'true'}
  style="background-image: {background}"
  on:click={toggleOptions}
>
  <h1>{name}</h1>
</button>

<style>
  .compCard {
    display: flex;
    flex-direction: column;
    align-items: start;
    vertical-align: top;
    background-color: var(--bg-alt);
    padding: 10px;
    border-radius: 10px;
    will-change: filter;
    transition:
      filter 200ms,
      border-color 100ms;
    border: 1px solid var(--bg-border);
  }
</style>
