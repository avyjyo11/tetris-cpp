bld:
	cd build && cmake .. && make

run:
	./build/Tetris

br:
	make bld && make run