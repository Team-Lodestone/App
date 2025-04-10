// region l10n
import { getLocaleFromNavigator, init, register } from 'svelte-i18n'
import { initLUILanguages } from '@team-lodestone/lodestone-ui'

// @ts-expect-error But I've already done this?
register('en', async () => await import('./assets/L10N/en.json'))

const getLanguage = (): string | null => {
  const lang = localStorage.getItem('language')

  if (lang && lang !== 'default') return lang
  else return getLocaleFromNavigator()
}

export const initL10N = async (): Promise<void> => {
  // @ts-ignore couldn't use svelte-i18n's type since unexported
  await initLUILanguages({
    fallbackLocale: 'en-US',
    initialLocale: getLanguage(),
    warnOnMissingMessages: true
  })
  await init({ fallbackLocale: 'en-US', initialLocale: getLanguage(), warnOnMissingMessages: true })
}
// endregion
