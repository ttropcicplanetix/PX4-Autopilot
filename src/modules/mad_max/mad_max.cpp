#include "mad_max.h"

MadMax::MadMax()
{
	// Do nothing in Constructor
}

void MadMax::run()
{
	static vehicle_local_position v_position{};
	hrt_abstime now = hrt_absolute_time();


	// New topic data has been received
	while(!should_exit())
	{
		static _vehicle_local_position_s v_position{};
		hrt_abstime now = hrt_absolute_time();

		// New topic data has been received
		 if(_vehicle_local_position_sub.update(&v_position))
		 {

		const Vector2f vehicle_xy_vel{v_position.vx, v_position_vy};
		const float vehicle_speed_m_s = vehicle_xy_vel.norm();¸

		if(vehicle_speed_m_s <1.0f){
			PX4_INFO("Come on, we're too slow");

		}
		else if(vehicle_speed_m_s <3.0f)
		{
			PX4_INFO("We're getting there");
		}

		else {
			PX4_INFO("Wait, a bit too fast");
		}


	}

		// Sleep for 1s to run the print statement at 1Hz max
		px4_sleep(1_s);



}

// ModuleBase related functions (below)
int MadMax::task_spawn(int argc, char *argv[])
{
	px4_main_t entry_point = (px4_maint_t)&run_trampoline;

	int _task_id = px4_task_spawn_cmd("mad_max", SCHED_DEFAULT,
					   SCHED_PRIORITY_DEFAULT, 1500, entry_point, (char *const)argv);

	if(_task_id < 0)
	{
		PX4_INFO("Max Max Module instantiation Failed");
		_task_id = -1;
		return -errno;

	}
	else
	{
		return PX4_OK;
	}
}

MadMax *MadMax::instantiate(int argc, char *argv[])
{
	return new MadMax();
}

int MadMax::print_usage(const char *reason)
{
	if(reason)
	{
		PX4_WARN("%s\n", reason);

	}

	PRINT_MODULE_USAGE_NAME("mad_max", "dev_summit_2022");
	PRINT_MODULE_USAGE_COMMAND("start");
	PRINT_MODULE_USAGE_DEFAULT_COMMANDS();

	return 0;
}



int MadMax::custom_command(int argc, char *argv[])
{
	return print_usage("Unrecognized command");
}

// Main entry point function for PX4 NuttX System
int mad_max_main(int argc, char *argv[])
{
	return MadMax::main(argc, argv);
}
