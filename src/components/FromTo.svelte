<script lang="ts">
  type Direction = 'left' | 'right'

  export let direction: Direction = 'right'
  export let first: string
  export let last: string
</script>

<div style="display:flex;flex-direction:row;gap:10px;justify-content:center;align-items:center">
  <div class="ft">{first}</div>
  <i class="fa-solid {direction === 'right' ? 'fa-arrow-right' : 'fa-arrow-left'}"></i>
  <div class="ft">{last}</div>
</div>

<style>
  .ft {
    width: 50px;
    text-align: center;
    padding: 10px;
    border-radius: 10px;
    background-color: var(--bg-alt);
  }
</style>
