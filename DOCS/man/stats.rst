STATS
=====

This builtin script displays information and statistics for the currently
played file. It is enabled by default if mpv was compiled with Lua support.
It can be disabled entirely using the ``--load-stats-overlay=no`` option.

Usage
-----

The following key bindings are active by default unless something else is
already bound to them:

====   ==============================================
i      Show stats for a fixed duration
I      Toggle stats (shown until toggled again)
?      Toggle displaying the key bindings
====   ==============================================

While the stats are visible on screen the following key bindings are active,
regardless of existing bindings. They allow you to switch between *pages* of
stats:

====   ==================
1      Show usual stats
2      Show frame timings (scroll)
3      Input cache stats
4      Active key bindings (scroll)
5      Selected Tracks Info (scroll)
0      Internal stuff (scroll)
====   ==================

If stats were displayed by toggling, these key bindings are also active:

====   ==================
ESC    Close the stats
====   ==================

On pages which support scroll, these key bindings are also active:

====   ==================
UP     Scroll one line up
DOWN   Scroll one line down
====   ==================

On page 4, these key bindings are also active:

====   ==================
/      Search key bindings
====   ==================

Configuration
-------------

This script can be customized through a config file ``script-opts/stats.conf``
placed in mpv's user directory and through the ``--script-opts`` command-line
option. The configuration syntax is described in `mp.options functions`_.

Configurable Options
~~~~~~~~~~~~~~~~~~~~

``key_page_1``
    Default: 1
``key_page_2``
    Default: 2
``key_page_3``
    Default: 3
``key_page_4``
    Default: 4
``key_page_5``
    Default: 5
``key_page_0``
    Default: 0
``key_exit``
    Default: ESC

    Key bindings for page switching while stats are displayed.

``key_scroll_up``
    Default: UP
``key_scroll_down``
    Default: DOWN
``key_scroll_search``
    Default: /
``scroll_lines``
    Default: 1

    Scroll key bindings and number of lines to scroll on pages which support it.

``duration``
    Default: 4

    How long the stats are shown in seconds (oneshot).

``redraw_delay``
    Default: 1

    How long it takes to refresh the displayed stats in seconds (toggling).

``persistent_overlay``
    Default: no

    When `no`, other scripts printing text to the screen can overwrite the
    displayed stats. When `yes`, displayed stats are persistently shown for the
    respective duration. This can result in overlapping text when multiple
    scripts decide to print text at the same time.

``file_tag_max_length``
    Default: 128

    Only show file tags shorter than this length, in bytes.

``file_tag_max_count``
    Default: 16

    Only show the first specified amount of file tags.

``term_clip``
    Default: yes

    Whether to clip lines to the terminal width.

``plot_perfdata``
    Default: no

    Show graphs for performance data (page 2).

``plot_vsync_ratio``
    Default: no

``plot_vsync_jitter``
    Default: no

    Show graphs for vsync and jitter values (page 1). Only when toggled.

``plot_cache``
    Default: yes

    Show graphs for cache values (page 3). Only when toggled.

``plot_tonemapping_lut``
    Default: no

    Enable tone-mapping LUT visualization automatically. Only when toggled.

``flush_graph_data``
    Default: yes

    Clear data buffers used for drawing graphs when toggling.

``font``
    Default: same as ``osd-font``

    Font name. Should support as many font weights as possible for optimal
    visual experience.

``font_mono``
    Default: monospace

    Font name for parts where monospaced characters are necessary to align
    text. Currently, monospaced digits are sufficient.

``font_size``
    Default: 20

    Font size used to render text.

``font_color``
    Default: same as ``osd-color``

    Color of the text.

``border_size``
    Default: 1.65

    Size of border drawn around the font.

``border_color``
    Default: same as ``osd-border-color``

    Color of the text border.

``shadow_x_offset``
    Default: same as ``--osd-shadow-offset``

    The horizontal distance from the text to position the shadow at.

``shadow_y_offset``
    Default: same as ``--osd-shadow-offset``

    The vertical distance from the text to position the shadow at.

``shadow_color``
    Default: same as ``osd-shadow-color``

    Color of the text shadow.

``alpha``
    Default: 11

    Transparency of text when ``font_color`` is specified, of text borders when
    ``border_color`` is specified, and of text shadows when ``shadow_color`` is
    specified.

``plot_bg_border_color``
    Default: 0000FF

    Border color used for drawing graphs.

``plot_bg_border_width``
    Default: 1.25

    Border width used for drawing graphs.

``plot_bg_color``
    Default: 262626

    Background color used for drawing graphs.

``plot_color``
    Default: FFFFFF

    Color used for drawing graphs.

``vidscale``
    Default: auto

    Scale the text and graphs with the video.
    ``no`` tries to keep the sizes constant.
    ``auto`` scales the text and graphs with the OSD, which is scaled with the
    window or kept at a constant size, depending on the ``--osd-scale-by-window`` option.

Note: colors are given as hexadecimal values and use ASS tag order: BBGGRR
(blue green red).

Different key bindings
~~~~~~~~~~~~~~~~~~~~~~

Additional keys can be configured in ``input.conf`` to display the stats::

    e script-binding stats/display-stats
    E script-binding stats/display-stats-toggle

And to display a certain page directly::

    i script-binding stats/display-page-1
    h script-binding stats/display-page-4-toggle

Active key bindings page
~~~~~~~~~~~~~~~~~~~~~~~~

Lists the active key bindings and the commands they're bound to, excluding the
interactive keys of the stats script itself. See also ``--input-test`` for more
detailed view of each binding.

The keys are grouped automatically using a simple analysis of the command
string, and one should not expect documentation-level grouping accuracy,
however, it should still be reasonably useful.

Using ``--idle --script-opt=stats-bindlist=yes`` will print the list to
the terminal and quit immediately. Long lines are clipped to the terminal width
unless this is disabled with ``--script-opt=stats-term_clip=no``. Escape
sequences can be disabled by adding ``-`` before ``yes``, i.e.
``--script-opt=stats-bindlist=-yes``.

Like with ``--input-test``, the list includes bindings from ``input.conf`` and
from user scripts. Use ``--no-config`` to list only built-in bindings.

Internal stuff page
~~~~~~~~~~~~~~~~~~~

Most entries shown on this page have rather vague meaning. Likely none of this
is useful for you. Don't attempt to use it. Forget its existence.

Selecting this for the first time will start collecting some internal
performance data. That means performance will be slightly lower than normal for
the rest of the time the player is running (even if the stats page is closed).
Note that the stats page itself uses a lot of CPU and even GPU resources, and
may have a heavy impact on performance.

The displayed information is accumulated over the redraw delay (shown as
``poll-time`` field).

This adds entries for each Lua script. If there are too many scripts running,
parts of the list will simply be out of the screen, but it can be scrolled.

If the underlying platform does not support pthread per thread times, the
displayed times will be 0 or something random (I suspect that at time of this
writing, only Linux provides the correct via pthread APIs for per thread times).

Most entries are added lazily and only during data collection, which is why
entries may pop up randomly after some time. It's also why the memory usage
entries for scripts that have been inactive since the start of data collection
are missing.

Memory usage is approximate and does not reflect internal fragmentation.

JS scripts memory reporting is disabled by default because collecting the data
at the JS side has an overhead and will increase memory usage. It can be
enabled by setting the ``--js-memory-report`` option before starting mpv.

If entries have ``/time`` and ``/cpu`` variants, the former gives the real time
(monotonic clock), while the latter the thread CPU time (only if the
corresponding pthread API works and is supported).
