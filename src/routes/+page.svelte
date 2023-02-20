<script>
  import Greet from "$lib/Greet.svelte";

  import Vite from "$lib/vite.svg"
  import Tauri from "$lib/tauri.svg"
  import Svelte from "$lib/svelte.svg"
</script>

<h1>Welcome to Tauri!</h1>

<div class="row">
  <a href="https://vitejs.dev" target="_blank" rel="noreferrer">
    <img src={Vite} class="logo vite" alt="Vite Logo" />
  </a>
  <a href="https://tauri.app" target="_blank" rel="noreferrer">
    <img src={Tauri} class="logo tauri" alt="Tauri Logo" />
  </a>
  <a href="https://kit.svelte.dev" target="_blank" rel="noreferrer">
    <img src={Svelte} class="logo svelte" alt="Svelte Logo" />
  </a>
</div>

<p>Click on the Tauri, Vite, and Svelte logos to learn more.</p>

<div class="row">
  <Greet />
</div>

<style>
  .logo.vite:hover {
    filter: drop-shadow(0 0 2em #747bff);
  }

  .logo.svelte:hover {
    filter: drop-shadow(0 0 2em #ff3e00);
  }
</style>
