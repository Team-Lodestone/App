import { defineConfig } from 'vite'
import { svelte } from '@sveltejs/vite-plugin-svelte'
import { VitePWA } from 'vite-plugin-pwa'
import legacy from '@vitejs/plugin-legacy';
import babel from 'vite-plugin-babel';

export default defineConfig({
  base: '/App',
  plugins: [
    svelte(),
    VitePWA({
      registerType: 'autoUpdate',
      devOptions: {
        enabled: true
      },
      workbox: {
        maximumFileSizeToCacheInBytes: 10000000
      },
      manifest: {
        name: 'Project Lodestone',
        description: 'Edit, Convert and Transform Minecraft Worlds',
        theme_color: '#121212',
        background_color: '#121212',
        display: 'standalone',
        start_url: '/',
        icons: [
          {
            src: '/App/assets/Lodestone_Favicon.png',
            sizes: '512x512',
            type: 'image/png'
          },
          {
            src: '/App/assets/Lodestone_Favicon_192x192.png',
            sizes: '192x192',
            type: 'image/png'
          },
          {
            src: '/App/assets/Lodestone_Favicon_Mono.png',
            sizes: '512x512',
            type: 'image/png',
            purpose: 'monochrome'
          },
          {
            src: '/App/assets/Lodestone_Favicon_Maskable.png',
            sizes: '512x512',
            type: 'image/png',
            purpose: 'maskable'
          }
        ],
        file_handlers: [
          {
            action: '/App/pwa-arc',
            accept: {
              'application/octet-stream': ['.arc']
            }
          },
          {
            action: '/App/pwa-loc',
            accept: {
              'application/octet-stream': ['.loc']
            }
          },
          {
            action: '/App/pwa-msscmp',
            accept: {
              'application/octet-stream': ['.msscmp']
            }
          },
          {
            action: '/App/pwa-col',
            accept: {
              'application/octet-stream': ['.col']
            }
          },
          {
            action: '/App/pwa-grf',
            accept: {
              'application/octet-stream': ['.grf']
            }
          },
          {
            action: '/App/pwa-nbt',
            accept: {
              'application/octet-stream': ['.nbt', '.snbt'],
            }
          }
        ]
      }
    })
  ]
})
