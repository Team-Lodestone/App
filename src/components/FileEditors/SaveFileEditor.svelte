<script lang="ts">
  import { type LodestoneFile, type TreeNode } from '../../Lodestone.js'

  export let save: TreeNode<LodestoneFile>

  /* This is the subpage inside FileEditor that lets you change properties of the Save File */
</script>

<div class="SaveFileEditor">
  <h1>Name: {save.file.name}</h1>
  {#if save.fileType === 'save'}
    <h1>Offset: {save.cppType.indexOffset}</h1>
  {/if}
  <h1>Size: {save.file.size}</h1>
</div>

<style>
  .SaveFileEditor {
    display: flex;
    flex-direction: column;
  }
</style>
