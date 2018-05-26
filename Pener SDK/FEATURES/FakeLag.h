#pragma once

namespace SDK
{
	class CUserCmd;
}

class CFakeLag
{
public:
	void do_fakelag(SDK::CUserCmd* cmd);
};

extern CFakeLag* fakelag;