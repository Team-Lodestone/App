// region SaveEditor
export type platforms =
  | 'Xbox 360'
  | 'Xbox One'
  | 'PS3'
  | 'PSVita'
  | 'PS4'
  | 'Wii U'
  | 'Nintendo Switch'
export type compressionMethods = 'None' | 'LZX' | 'Vita RLE' | 'Zlib' | 'Deflate'

export interface search {
  type: 'str' | 'regex'
  value: string | null | RegExp
}

export interface InnerFileType {
  savegame: search
  thumb?: search
  region?: search
  metadata?: search
  large_image?: search
  settings?: { save_must_match_thumb_filename: boolean; thumb_ext_size: number }
}
// endregion
