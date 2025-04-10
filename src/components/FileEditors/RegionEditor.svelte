<script lang="ts">
  import { type LodestoneFile, type TreeNode } from '../../Lodestone.js'

  export let region: TreeNode<LodestoneFile>
</script>

<div class="RegionEditor">
  {#if region.fileType === 'region' && region.cppType}
    <h1>Location: {region.cppType.x}, {region.cppType.z}</h1>
    <h1>Dimension: {region.cppType.dim}</h1>
  {/if}
  <h1>Filename: {region.file.name}</h1>
</div>

<style>
  .RegionEditor {
    display: flex;
    flex-direction: column;
  }
</style>
