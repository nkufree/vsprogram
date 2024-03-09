#include<iostream>
#include<fstream>
#include<cstring>
#include<vector>
#include<map>
#include<Windows.h>
#include"tinystr.h"
#include"tinyxml.h"

using namespace std;
map<string, int> keyAlter = { {"C",0},{"bD",-1},{"D",-2} };
int musicDivision = 0;
int music2piano[9][12] = {  0,0,0,0,0,0,0,0,0,21,22,23,
							24,25,26,27,28,29,30,31,32,33,34,35,
							36,37,38,39,40,41,42,43,44,45,46,47,
							48,49,50,51,52,53,54,55,56,57,58,59,
							60,61,62,63,64,65,66,67,68,69,70,71,
							72,73,74,75,76,77,78,79,80,81,82,83,
							84,85,86,87,88,89,90,91,92,93,94,95,
							96,97,98,99,100,101,102,103,104,105,106,107
							,108,0,0,0,0,0,0,0,0,0,0,0 };
int moveDis = 1;
//定义音阶的加法
class Step
{
public:
	string m_step;
	int m_octave;
	Step(string s,int octave):m_octave(octave) { m_step = s; }
	string operator+(int b)
	{
		string stepList[12] = { "1","#1","2","#2","3","4","#4","5","#5","6","#6","7" };
		map<string, int> step2num = { {"C",0},{"D",2},{"E",4},{"F",5},{"G",7},{"A",9},{"B",11} };
		int index = step2num[m_step] + b;
		if (index < 0)
		{
			m_octave--;
			index += 12;
		}
		else if (index > 11)
		{
			m_octave++;
			index -= 12;
		}
		return stepList[index % 12];
	}
	int showNoteNumber(int b)
	{
		string stepList[12] = { "1","#1","2","#2","3","4","#4","5","#5","6","#6","7" };
		map<string, int> step2num = { {"C",0},{"D",2},{"E",4},{"F",5},{"G",7},{"A",9},{"B",11} };
		int index = step2num[m_step] + b;
		if (index < 0)
		{
			m_octave--;
			index += 12;
		}
		else if (index > 11)
		{
			m_octave++;
			index -= 12;
		}
		return index % 12;
	}
};
//音符
class Note 
{
	string m_step;
	string m_alter;
	string m_octave;
	int m_dur;
public:
	Note() {}
	Note(string step, string alter, string octave):m_step(step),m_alter(alter),m_octave(octave){}
	void setStep(string step) { m_step = step; }
	void setAlter(string alter) { m_alter = alter; }
	void setOctave(string octave) { m_octave = octave; }
	void setDur(int dur) { m_dur = dur; }
	int getDur() { return m_dur; }
	string getNumber(int keyAlt)
	{
		if (m_step.length() != 1)
		{
			cout << "m_step错误";
			return "";
		}
		if (m_step == " ")return "0";

		const char* alt = m_alter.data();
		const char* oct = m_octave.data();
		int totalAlt = keyAlt + atoi(alt);
		Step s(m_step, atoi(oct));
		return s + totalAlt;
	}
	string getNumber2(int keyAlt)
	{
		if (m_step.length() != 1)
		{
			cout << "m_step错误";
			return "";
		}
		if (m_step == " ")return "0";

		const char* alt = m_alter.data();
		const char* oct = m_octave.data();
		int totalAlt = keyAlt + atoi(alt);
		Step s(m_step, atoi(oct));
		string noteNum = s + totalAlt;
		int octNew = s.m_octave;
		string final;
		switch (octNew)
		{
		case 3:
			final = "(" + noteNum + ")";
			break;
		case 4:
			final = noteNum;
			break;
		case 5:
			final = "[" + noteNum + "]";
			break;
		}
		return final;
	}
	int getNumber3(int keyAlt)
	{
		if (m_step.length() != 1)
		{
			cout << "m_step错误";
			return -1;
		}
		if (m_step == " ") 
		{

			return 0;
		}

		const char* alt = m_alter.data();
		const char* oct = m_octave.data();
		int totalAlt = atoi(alt);
		Step s(m_step, atoi(oct));
		int noteNum = s.showNoteNumber(totalAlt);
		int octNew = s.m_octave;
		int final = music2piano[octNew - 1][noteNum];
		return final;
	}
	int* getContinue() {
		int* p = new int[2];//[需要中继器个数，最后一个中继器的时值]
		int thisDur = m_dur;
		p[0] = 1;
		while (thisDur > musicDivision)
		{
			p[0]++;
			thisDur -= musicDivision;
		}
		if (thisDur == musicDivision)
			p[1] = 4;
		else if (thisDur * 4 == musicDivision * 3)
			p[1] = 3;
		else if (thisDur * 4 == musicDivision)
			p[1] = 1;
		else
			p[1] = 2;
		return p;

	}
};

//小节
class Measure
{
public:
	vector<Note*>* notes;
	int number;
	Measure() { notes = new vector<Note*>; }
	Measure(int n):number(n){ notes = new vector<Note*>; }
};


//乐曲
class Music
{
	int m_divisions;
	string m_key;
	
public:
	vector<Measure*>* measures;
	Music() { measures = new vector<Measure*>; }
	void setDivisions(int div) { m_divisions = div; musicDivision = div; }
	int getDivisions() { return m_divisions; }
	void setKey(string key) { m_key = key; }
	string getKey() { return m_key; }
};

void changeColor(int dur,int div)
{
	if (dur == div)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		return;
	}
	else if (div == 2 * dur)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
		return;
	}
	else if (2 * div == 3 * dur)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		return;
	}
	else if (dur == 2 * div)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		return;
	}
	else if (dur == 3 * div)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		return;
	}
	else if (dur == 4 * div)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
		return;
	}
}


int main()
{
	TiXmlDocument doc("tricolor.musicxml");
	bool loadOK = doc.LoadFile();
	if (!loadOK)
	{
		cout << "打开失败" << endl;
		return 0;
	}
	Music* myMusic = new Music();

	TiXmlElement* root = doc.RootElement();
	TiXmlNode* part = root->FirstChild("part");
	//遍历measure节点（小节）
	//cout << "|";
	if (TiXmlNode* a = part->FirstChild("measure")->FirstChild("attributes")->FirstChild("divisions"))
	{
		//cout << a->ToElement()->GetText() << endl;
		myMusic->setDivisions(atoi(a->ToElement()->GetText()));
	}
	if (TiXmlNode* a = part->FirstChild("measure")->FirstChild("attributes")->FirstChild("key")->FirstChild("fifths"))
	{
		string fifths = a->ToElement()->GetText();
		//cout << fifths << endl;
		if (fifths == "-5")
			myMusic->setKey("bD");
	}
	int measureNumber = 0;
	for (TiXmlNode* measure = part->FirstChild("measure");measure; measure = measure->NextSibling("measure"))
	{
		measureNumber++;
		Measure* myMeasure = new Measure(measureNumber);
		//遍历note节点（各个音符）
		for (TiXmlNode* note = measure->FirstChild("note"); note; note = note->NextSibling("note"))
		{
			string step = " ", alter = "0", octave = " ";
			if (note->FirstChild("rest"))
			{
				//cout << "{0} ";
			}
			if (TiXmlNode * pitch = note->FirstChild("pitch"))
			{
				
				if (TiXmlNode* a = pitch->FirstChild("step"))
					step = a->ToElement()->GetText();
				if (TiXmlNode* a = pitch->FirstChild("alter"))
					alter = a->ToElement()->GetText();
				if (TiXmlNode* a = pitch->FirstChild("octave"))
					octave = a->ToElement()->GetText();
				//cout << "[" << step << "," << alter << "," << octave << "] ";
			}
			/*if (TiXmlNode* a = note->FirstChild("type"))
			{
				string type = a->ToElement()->GetText();
				cout << type << " ";
			}*/
			Note* myNote = new Note(step, alter, octave);
			if (TiXmlNode* a = note->FirstChild("duration"))
			{
				const char* duration = a->ToElement()->GetText();
				//cout << duration << " ";
				myNote->setDur(atoi(duration));
			}
			
			myMeasure->notes->push_back(myNote);
		}
		myMusic->measures->push_back(myMeasure);
		//cout << "|" << endl;
	}
	//cout << "四分音符：灰色，" << endl;

	ofstream outFunc("outFunc.txt");

	for (vector<Measure*>::iterator it = myMusic->measures->begin(); it != myMusic->measures->end(); ++it)
	{
		vector<Note*>* noteList = (*it)->notes;
		for (vector<Note*>::iterator noteIt = noteList->begin(); noteIt != noteList->end(); ++noteIt)
		{
			//changeColor((*noteIt)->getDur(),myMusic->getDivisions());
			int pianoNum = (*noteIt)->getNumber3(keyAlter[myMusic->getKey()]);
			int* exDis = (*noteIt)->getContinue();
			cout << exDis[0] << ";" << exDis[1] << " ";
			outFunc << "setblock ~" << moveDis << " ~ ~ grass_block" << endl;
			if (pianoNum != 0)
				outFunc << "setblock ~" << moveDis << " ~1 ~ minecraft:command_block{Command:\"playsound minecraft:lkrb.piano.p" << pianoNum << "fff record @a ~ ~ ~\"}" << endl;
			else
				outFunc << "setblock ~" << moveDis << " ~1 ~ minecraft:command_block" << endl;
			if (exDis[0] == 1)
			{
				outFunc << "setblock ~" << moveDis + 1 << " ~ ~ minecraft:repeater[facing=west,delay=" << exDis[1] << "]" << endl;
				moveDis += 2;
			}
			else
			{
				for (int amsm = 1; amsm < exDis[0]; amsm++)
				{
					outFunc << "setblock ~" << moveDis + amsm << " ~ ~ minecraft:repeater[facing=west,delay=4]" << endl;
				}
				outFunc << "setblock ~" << moveDis + exDis[0] << " ~ ~ minecraft:repeater[facing=west,delay=" << exDis[1] << "]" << endl;
				moveDis += exDis[0] + 1;
			}
			
		}
		cout << endl;
	}

	return 0;
}