import { type LoadingScreenParams, LoadingScreenParamStore } from './store'

export class LoadingScreen {
  private store: LoadingScreenParams

  public constructor() {
    LoadingScreenParamStore.subscribe((value) => {
      this.store = value
    })
  }
  // I prefer getProgress setProgress but whatever
  public set progress(progress: number) {
    LoadingScreenParamStore.set({ progress, isLoading: true, title: this.title })
  }

  public get progress(): number {
    return this.store.progress
  }

  public set title(title: string) {
    LoadingScreenParamStore.set({ progress: this.progress, isLoading: this.shown, title })
  }

  public get title(): string {
    return this.store.title
  }

  public get shown(): boolean {
    return this.store.isLoading
  }

  public set shown(shown: boolean) {
    LoadingScreenParamStore.set({ progress: 0, isLoading: shown, title: '' })
  }
}
