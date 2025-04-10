import './assets/main.css'
// import 'core-js/stable'
// import 'regenerator-runtime/runtime'
import { mount } from 'svelte'
import App from './App.svelte'
import { LoadingScreen } from './loadingScreen'
import { initL10N } from './L10N'

// @ts-ignore because it works anyways...
export { version } from '../package.json'

let app: { $set?: never; $on?: never } | undefined = undefined

async function initApp(): Promise<Record<never, never>> {
  await initL10N()

  // Vite is being really dumb on my machine, so this fixes double mounting the App bc it throws if the element doesn't exist
  document.getElementById('unsupportedMessage').remove()
  return mount(App, {
    target: document.getElementById('app')!
  })
}
// if we don't wait for initL10N we get locale loading race condition afaik
initApp().then((mounted) => {
  app = mounted
})

export default app

export const loadingScreen: LoadingScreen = new LoadingScreen()

export const onFilesChosen = (event: Event): FileList => {
  const input = event.target as HTMLInputElement
  return input.files!
}
