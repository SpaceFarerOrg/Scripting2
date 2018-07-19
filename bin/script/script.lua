function Update()
	--DrawLine(0,0,1600,900)
	--DrawLine(0,900,1600,0)
	--Print("Hello :D")
	--DrawText("Hello", 762, 431)
end

goalId = 0
ranThroughCPs = 0
amountOfCPs = 0

function Init()

	SetGoalPosition(300, 300);

	RegisterTriggerCallback("OnEnter", goalId)
	
	AddCheckpoint(10,10)
	RegisterTriggerCallback("OnEnter", 1)
	
	AddCheckpoint(600,10)
	RegisterTriggerCallback("OnEnter", 2)
	
	AddCheckpoint(10,600)
	RegisterTriggerCallback("OnEnter", 3)
	
	AddCheckpoint(600,600)
	RegisterTriggerCallback("OnEnter", 4)
	
	amountOfCPs = 4
end

function OnEnter(id)
--	ranThroughCPs++
--	
--	if(amountOfCPs == ranThroughCPs)
--		UnlockGoal();
--	end
--	
--	if(id == goalId)
--		Win()
--	end
--	
--	UnregisterTriggerCallback(id)
end