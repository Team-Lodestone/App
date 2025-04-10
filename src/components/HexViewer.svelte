<script lang="ts">
  // NOT WORKING ATM
  export let data: Uint8Array
  let offset = 0

  // https://stackoverflow.com/a/55200387
  const hexLookup = []

  for (let n = 0; n <= 0xff; ++n) {
    const hexOctet = n.toString(16).padStart(2, '0')
    hexLookup.push(hexOctet)
  }

  function hex(buff: Uint8Array, start: number, end: number): string {
    start = Math.max(0, start)
    end = Math.min(buff.length, end)

    console.log(start, end)

    const sliced = buff.slice(start, end)

    const hex = []

    for (let i = 0; i < sliced.length; ++i) {
      hex.push(hexLookup[sliced[i]])
      if ((i + 1) % 16 === 0) {
        hex.push('\n')
      } else if (i !== sliced.length - 1) {
        hex.push(' ')
      }
    }

    return hex.join('')
  }

  function scroll(event): void {
    const scrollPos = event.target.scrollTop
    offset = Math.max(0, Math.ceil(scrollPos / 16) * 16)
  }
</script>

<pre class="hexViewer" on:scroll={scroll}>{hex(data, offset - 2048, offset + 2048)}</pre>
