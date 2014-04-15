mpd_visualizer
==============

Visualizer for MPD

Currently WIP
It assumes that MPD is configured to output music data to /tmp/mpd.fifo at 44100:16:1.
This can be archieved by adding this to your mpd.conf:
```
    audio_output {
      type          "fifo"
      name          "my_fifo"
      path          "/tmp/mpd.fifo"
      format        "44100:16:1"
    }
```

Available visualizers are a frequency spectrum and a sound wave like in NCMPCPP (thanks to its devs, their code helped me a lot).

If you want to write another visualizer, you can extend Visualizer or FreqVisualizer and add your Visualizer in main.cpp

To toggle between visualizers use "space", to quit ESC or q.
