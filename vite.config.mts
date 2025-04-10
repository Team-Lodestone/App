import { defineConfig } from 'vite'
import { svelte } from '@sveltejs/vite-plugin-svelte'
import { VitePWA } from 'vite-plugin-pwa'
import legacy from '@vitejs/plugin-legacy';
import babel from 'vite-plugin-babel';

export default defineConfig({
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
            src: '/assets/Lodestone_Favicon.png',
            sizes: '512x512',
            type: 'image/png'
          },
          {
            src: '/assets/Lodestone_Favicon_192x192.png',
            sizes: '192x192',
            type: 'image/png'
          },
          {
            src: '/assets/Lodestone_Favicon_Mono.png',
            sizes: '512x512',
            type: 'image/png',
            purpose: 'monochrome'
          },
          {
            src: '/assets/Lodestone_Favicon_Maskable.png',
            sizes: '512x512',
            type: 'image/png',
            purpose: 'maskable'
          }
        ],
        file_handlers: [
          {
            action: '/pwa-arc',
            accept: {
              'application/octet-stream': ['.arc']
            }
          },
          {
            action: '/pwa-loc',
            accept: {
              'application/octet-stream': ['.loc']
            }
          },
          {
            action: '/pwa-msscmp',
            accept: {
              'application/octet-stream': ['.msscmp']
            }
          },
          {
            action: '/pwa-col',
            accept: {
              'application/octet-stream': ['.col']
            }
          },
          {
            action: '/pwa-grf',
            accept: {
              'application/octet-stream': ['.grf']
            }
          },
          {
            action: '/pwa-nbt',
            accept: {
              'application/octet-stream': ['.nbt', '.snbt'],
            }
          }
        ]
      }
    })
  ]
})
