function Component() 
{ 
    // default constructor 
} 
 
Component.prototype.createOperations = function() 
{ 
    component.createOperations(); 
	component.addOperation("CreateShortcut", "@TargetDir@/DayPlanner.exe", "@StartMenuDir@/DayPlanner.lnk", "workingDirectory=@TargetDir@"); 
} 
