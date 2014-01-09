#LD_PRELOAD="/usr/lib/libprofiler.so" CPUPROFILE=bench.prof CPUPROFILE_FREQUENCY=10000 blenderplayer -w 1600 900 -g show_framerate = 1 -g show_profile = 1 blends/anim_stress_xheavy.blend

while [ 1 ]; do
	blenderplayer -w 1600 900 -g show_framerate = 1 -g show_profile = 1 blends/anim_stress_xheavy.blend && break;
done
