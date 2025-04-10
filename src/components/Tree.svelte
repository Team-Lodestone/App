<script lang="ts">
  import { type LodestoneFile, type TreeNode } from '../Lodestone'

  export let tree: TreeNode<LodestoneFile>[]
  export let onClick = (node?: TreeNode<LodestoneFile>): void => {}
  export let onExpand = (node?: TreeNode<LodestoneFile>): void => {}

  let expansion = {}

  const toggleExpansion = (node: TreeNode<LodestoneFile>) => {
    onExpand(node)
    expansion[node.file.name] = !expansion[node.file.name]
  }

  // todo: needs to auto react to new folder being added while already expanded
  // todo: allow for naming or importing directory
  // same with files.
  // probably show a menu when you click + with these options
  export function addSubfolder(t: TreeNode<LodestoneFile>, name: string): void {
    if (!t.children.map((c) => c.file.name).includes(name)) {
      t.children = [
        ...t.children,
        { file: { name, buffer: new Uint8Array(), size: 0 }, children: [], type: 'directory' }
      ]
    }
  }
</script>

<ul>
  {#each tree as t (t.file.name)}
    <li>
      {#if (t.children && t.children.length > 0) || (t.type && t.type === 'directory')}
        <button
          class="treeExpander"
          title={t.file.name}
          style="display:flex;align-items:center;justify-content:space-between;width:100%;"
          on:click={() => toggleExpansion(t)}
        >
          <div style="display:flex;align-items:center;gap:5px;padding:10px;">
            <span>{!expansion[t.file.name] ? '🗀' : '🗁'}</span>
            {t.file.name}
          </div>

          <span class="fileAction" style="margin-right:10px;">
            <a
              title="Add folder"
              on:click={(e) => {
                e.stopPropagation()
                addSubfolder(t, 'ass')
              }}>+</a
            >
          </span>
        </button>

        {#if expansion[t.file.name]}
          {#each t.children as child (child.file.name)}
            <div class="treeSubChild">
              <svelte:self tree={[child]} {onClick} />
            </div>
          {/each}
        {/if}
      {:else}
        <button class="treeChild" title={t.file.name} on:click={() => onClick(t)}>
          {t.file.name}
        </button>
      {/if}
    </li>
  {/each}
</ul>

<style>
  .treeChild,
  .treeExpander {
    /*padding: 0;*/
    background-color: transparent;
    width: 100%;
    border: 1px solid var(--bg-alt);

    text-align: left;
    border-radius: 0;
  }

  .treeSubChild,
  .treeChild,
  .treeExpander {
    background-color: transparent !important;
  }

  .treeExpander {
    border: 1px solid var(--bg-alt);
  }

  .treeSubChild {
    width: 100%;
    background-color: transparent !important;
    padding-left: 5px;
  }

  .treeSubChild ul li {
    background-color: transparent !important;
  }

  .treeExpander {
    padding: 0 !important;
  }

  .fileAction {
    cursor: pointer;
  }

  ul {
    margin-left: 0;
    list-style-type: none;
    padding-left: 0;
  }
</style>
