<script lang="ts">
  import logo from '../assets/Lodestone.svg'
  import type { LoadingScreenParams } from '../store'
  import { ProgressBar } from '@team-lodestone/lodestone-ui'

  export let params: LoadingScreenParams
</script>

<div id="loading">
  <img alt="logo" class="logo" src={logo} />
  <h1>{params.title}</h1>
  <ProgressBar max="100" value={params.progress} class="bar">{params.progress}%</ProgressBar>
</div>

<style>
  #loading .logo {
    position: absolute;
    top: 0;
  }

  #loading {
    width: 100%;
    height: 100%;
    display: flex;
    align-items: center;
    justify-content: center;
    flex-direction: column;
    align-content: center;
  }

  :global(#loading .bar) {
    width: 512px;
  }
</style>
