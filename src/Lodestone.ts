export type FileType = 'save' | 'thumb' | 'region'

export type TreeNode<T extends LodestoneFile> = {
  file?: T
  cppType?: never
  type?: 'file' | 'directory'
  fileType?: FileType
  children: TreeNode<T>[]
}

export type LodestoneFile = {
  name: string
  size: number
  offset?: number
  timestamp?: number
  cppType?: never
  fileType?: FileType
  buffer: Uint8Array
}

export function toFile(f: LodestoneFile): File {
  return new File([new Blob([f.buffer])], f.name, { lastModified: Number(f.timestamp) })
}

export async function fromFile(f: File): Promise<LodestoneFile> {
  return {
    name: f.name,
    buffer: new Uint8Array(await f.arrayBuffer()),
    timestamp: f.lastModified,
    size: f.size
  }
}
