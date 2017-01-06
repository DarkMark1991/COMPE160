## Sphinx The Game – Project Report

The screen displays a prompt (for example simply “left”, or something like “Travel east of North”) or a small riddle (“what’s up if up is down?”, “Red is blue, blue is yellow, yellow’s red and green’s the meadow.. so, what’s left?”), the answer to which is either a number, direction or color. (colors will be assigned to arrow keys). The player must press the corresponding button.

The duration of the game is predetermined (30 seconds for example). The score is calculated according to how many tasks the user has completed and how fast they did it.

The riddles are stored in “riddles.in” file which will follow a specific format: The first line contains only the number of riddles. All the other lines will look like this:
```<sequence_size> <sequence separated by spaces> <string description of the riddle>
```

After reading sequence size, the sequence is read one by one into sequence array and then the riddle text is read until the end of line.

The array is randomized by ShuffleArray function. I chose this option over just selecting the riddle by rand%/array_size to avoid duplicate questions.

QuizUser function will display the riddle to the player and wait until the user either completes the correct sequence, or fails. For now the fail gets 0 points and success (60 – answer time in seconds) %10, so the quicker the user answers the higher the score.

After 30 seconds the game stops and the number of correct answers and score are displayed and logged.

## Pseudocode:
```
STRUCT Riddle
	STRING str;
	INT seqSize;
	ARRAY INT sequence[4];

BEGIN ReadRiddles(arr, fileName)
	OPEN FILE filename
	READ n;
	FOR arr[i] as a; i=0 . . . n-1
		READ to a.seqSize;
		FOR j=0 ... a.seqSize-1
			READ a.sequence[j];
		READ TILL NEWLINE a.str
RETURN n;
END ReadRiddles

BEGIN ShuffleArray(array, size)
	FOR i < size
		Swap(array[i], array[rand()%size]);
END ShuffleArray

BEGIN QuizUser(Riddle r)
	PRINT r.str;
	startTime = time();
	FOR i = 0, i < r.sequenceSize
		READ KEY k;
		IF k IS NOT r.sequence[i] RETURN 0;
	RETURN (60-(time()-startTime))%10;
END QuizUser

BEGIN Sphinx(array, size)
	i = 0, score = 0, scoreSum = 0, correctCount = 0;
	ENTER redId;
	PRESS UP to start;
ShuffleArray(riddleArray, n);
	startTime = time();
	FOR EACH riddle IN riddleArray
		score = QuizUser(riddle);
IF time()–startTime<60 BREAK;
IF score>0 
correctCount++;
scoreSum += score; 
	PRINT scoreSum;
	LogRes(starttime, redid, correctCount, scoreSum); 
END Sphinx

BEGIN LogRes(starttime, redid, correctCount, scoreSum)
APPEND TO “sphinx.log”
<starttime> <redid> <correctCount> <scoreSum>;
END LogRes

BEGIN PrintLog()
	WHILE READ line FROM “sphinx.log”
		PRINT line;
END PrintLog

BEGIN MAIN
	size = ReadRiddles(riddleArray, “riddles.in”);
	TO PLAY PRESS UP 
		Sphinx(riddleArray, size);
	TO PRINT LOG PRESS RIGHT
		PrintLog();
	TO EXIT PRESS DOWN
		RETURN 0;
END MAIN
```
