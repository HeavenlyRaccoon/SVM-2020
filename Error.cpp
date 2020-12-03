#include "pch.h"
#include "Error.h"
namespace Error {
	ERROR errors[ERROR_MAX_ENTRY] = {
		ERROR_ENTRY(0, "Íåäîïóñòèìûé êîä îøèáêè"),
		ERROR_ENTRY(1, "Ñèñòåìíûé ñáîé"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Ïàğàìåòğ -in äîëæåí áûòü çàäàí"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Ïğåâûøåíà äëèíà âõîäíîãî ïàğàìåòğà"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),
		ERROR_ENTRY(109,"Ìàêñèìóì 3 ïàğàìåòğà(-in, -out, -log)"),
		ERROR_ENTRY(110, "Îøèáêà ïğè îòêğûòèè ôàéëà ñ èñõîäíûì êîäîì (-in)"),
		ERROR_ENTRY(111, "Íåäîïóñòèìûé ñèìâîë â èñõîäíîì ôàéëå (-in)"),
		ERROR_ENTRY(112, "Îøèáêà ïğè ñîçäàíèè ôàéëà ïğîòîêîëà (-log)"),
		ERROR_ENTRY(113, "Îøèáêà ïğè ÷òåíèè öåïî÷êè (íåïğàâèëüíûé ñèìâîë)"),
		ERROR_ENTRY(114, "Ïğåâûøåíèå äîïóñòèìîãî ğàçìåğà ïğè ñîçäàíèè òàáëèöû èäåíòèôèêàòîğîâ"),
		ERROR_ENTRY(115, "Òàáëèöà èäåíòèôèêàòîğîâ íå ñîçäàíà"),
		ERROR_ENTRY(116, "Äîñòèãíóòî ìàêñèìàëüíîå êîëè÷åñòâî ñòğîê â òàáëèöå èäåíòèôèêàòîğîâ"),
		ERROR_ENTRY(117, "Çíà÷åíèå íå íàéäåíî"),
		ERROR_ENTRY(118, "Ïğåâûøåíèå äîïóñòèìîãî ğàçìåğà ïğè ñîçäàíèè òàáëèöû ëåêñåì"),
		ERROR_ENTRY(119, "Òàáëèöà ëåêñåì íå ñîçäàíà"),
		ERROR_ENTRY(120, "Äîñòèãíóòî ìàêñèìàëüíîå êîëè÷åñòâî ñòğîê â òàáëèöå ëåêñåì"),
		ERROR_ENTRY(121, "Çíà÷åíèå íå íàéäåíî"),
		ERROR_ENTRY(122, "Â êîäå íå õâàòàåò ñêîáêè"),
		ERROR_ENTRY(123, "Ïåğåìåííàÿ íå èíèöèàëèçèğîâàíà!"),
		ERROR_ENTRY(124, "Âîçâàğàùàåìûé òèï íåñîîòâåòñâóåò âîçâğàùàåìîìó òèïó ôóíêöèè"),
		ERROR_ENTRY(125, "Îïåğàöèÿ ñ ğàçíûìè òèïàìè äàííûõ"),
		ERROR_ENTRY(126, "Îïåğàöèÿ íåäîïóñòèìà ñ ıòèì òèïîì äàííûõ"),
		ERROR_ENTRY_NODEF(127), ERROR_ENTRY_NODEF(128),
		ERROR_ENTRY_NODEF(129), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "Íåâåğíàÿ ñòğóêòóğà ïğîãğàììû!"),
		ERROR_ENTRY(601, "Îøèáî÷íûé îïåğàòîğ!"),
		ERROR_ENTRY(602, "Îøèáêà â âûğàæåíèè!"),
		ERROR_ENTRY(603, "Îøèáêà â âûğàæåíèè!"),
		ERROR_ENTRY(604, "Îøèáêà â ïàğàìåòğàõ ôóíêöèè!"),
		ERROR_ENTRY(605, "Îøèáêà â ïàğàìåòğàõ âûçûâàåìîé ôóíêöèè!"),
		ERROR_ENTRY_NODEF(606),
		ERROR_ENTRY_NODEF(607),
		ERROR_ENTRY_NODEF(608),
		ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610),ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),
		ERROR_ENTRY_NODEF10(640),ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),
		ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id) {
		if (id > 0 && id < ERROR_MAX_ENTRY) {
			ERROR error;
			error = errors[id];
			return error;
		}
		else {
			ERROR error;
			error = errors[0];
			return error;
		}
	}
	ERROR geterrorin(int id, int line = -1, int col = -1) {
		if (id > 0 && id < ERROR_MAX_ENTRY) {
			ERROR error;
			error = errors[id];
			error.inext.col = col;
			error.inext.line = line;
			return error;
		}
		else {
			return errors[0];
		}
	}
}