import { writable, type Writable } from 'svelte/store'
import { type compressionMethods, type platforms } from './types.js'

export type SaveFileEditorParams = {
  endian: number
  compression: compressionMethods
  file: File
  thumbnail: File
  thumbnailNameSize: number
  regions: File[]
  unknownFiles: File[]
  platform: platforms
}

export type LoadingScreenParams = {
  progress: number
  isLoading: boolean
  title: string
}

export const SaveFileEditorParamStore: Writable<SaveFileEditorParams> = writable({
  endian: 0,
  compression: 'None',
  file: null,
  thumbnail: null,
  thumbnailNameSize: 0,
  regions: [],
  unknownFiles: [],
  platform: 'Xbox 360'
})

export const LoadingScreenParamStore: Writable<LoadingScreenParams> = writable({
  progress: 0,
  isLoading: false,
  title: ''
})

// region Mobile UI
/** Store to get if the site should use mobile UI
 *
 * If the viewport's width is smaller than 710px, it is true.
 */
export const isMobile = writable(window.innerWidth < 710)

/** Sets if the site should use mobile UI
 *
 * Automatically called upon resize.
 */
export const setMobile = (): void => {
  isMobile.set(window.innerWidth < 710)
}
// endregion
