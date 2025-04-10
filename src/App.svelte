<script lang="ts">
  import { Router, Route, navigate } from 'svelte5-router'
  import Home from './pages/Home.svelte'
  import FileEditor from './pages/FileEditor.svelte'
  import { isLoading } from 'svelte-i18n'
  import { listen as addListener } from 'svelte5-router'
  import {
    isMobile,
    type LoadingScreenParams,
    LoadingScreenParamStore,
    type SaveFileEditorParams,
    SaveFileEditorParamStore,
    setMobile
  } from './store.js'
  import Loading from './pages/Loading.svelte'
  import { Topbar, ScreenAwareTopbarButton } from '@team-lodestone/lodestone-ui'
  import Settings from './pages/Settings.svelte'
  import NotFound from './pages/NotFound.svelte'

  let themeColor = '#AD95ED'
  let logo = '/assets/Lodestone_Logo.png'
  let bg = '/assets/LodestoneBg.jpg'
  let favicon = '/assets/Lodestone_Favicon.png'

  let path = window.location.pathname

  addListener(({ location }) => {
    path = location.pathname
  })

  $: topbarTransparent = path === '/' || path === '/Settings'

  let sfParams: SaveFileEditorParams
  SaveFileEditorParamStore.subscribe((value) => {
    sfParams = value
  })

  let lParams: LoadingScreenParams
  LoadingScreenParamStore.subscribe((value) => {
    lParams = value
  })

  const navigateSettings = (): void => {
    navigate('/Settings')
  }
</script>

<!--region head-->
<svelte:head>
  <title>Project Lodestone</title>
  <link rel="icon" href={favicon} />
  <link rel="shortcut icon" href={favicon} />
  <link rel="apple-touch-startup-image" href={favicon} />
  <link rel="apple-touch-icon" href={logo} />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <meta property="og:image" content={bg} />
  <meta property="og:type" content="website" />
  <meta property="theme-color" content={themeColor} />
  <meta
    name="description"
    content="Edit, Convert and Transform Minecraft Worlds and file formats"
  />
  <meta
    name="keywords"
    content="minecraft, lodestone, world converter, converter, legacy console edition, lce, java edition, java, documentation, bedrock edition, bedrock, pi edition, pi, 3ds edition, 3ds, Project Lodestone, MCS, ARC, savegame.dat, GRF, gamerule, PCK, MSSCMP, MCR, MCA, NBT, COL, LOC"
  />
  <meta name="msapplication-TileColor" content={themeColor} />
  <meta name="msapplication-TileImage" content={logo} />
  <meta name="application-name" content="Project Lodestone" />
  <meta
    name="msapplication-tooltip"
    content="Edit, Convert and Transform Minecraft Worlds and file formats"
  />
</svelte:head>
<!--endregion-->

{#if !$isLoading}
  {#if lParams.isLoading}
    <Loading params={lParams} />
  {/if}

  <Topbar
    logo={favicon}
    transparent={topbarTransparent}
    {isMobile}
    {setMobile}
    class={`${lParams.isLoading ? 'hidden' : ''}`}
  >
    <ScreenAwareTopbarButton
      {isMobile}
      href="https://Team-Lodestone.github.io/Documentation"
      mobileTitle="Documentation"
      title="Opens documentation for Project Lodestone and technical Minecraft info for all editions."
      usesIcon><i class="fa-solid fa-book"></i></ScreenAwareTopbarButton
    >
    <ScreenAwareTopbarButton
      {isMobile}
      onClick={navigateSettings}
      mobileTitle="Settings"
      title="Settings"
      usesIcon><i class="fa-solid fa-gear"></i></ScreenAwareTopbarButton
    >
  </Topbar>

  <div class={lParams.isLoading ? 'hidden' : ''}>
    <Router url="">
      <Route path="/"><Home /></Route>
      <Route path="/SaveFileEditor"><FileEditor params={sfParams} /></Route>
      <Route path="/Settings"><Settings /></Route>
      <Route path="*" component={NotFound} />
    </Router>
  </div>
{/if}
