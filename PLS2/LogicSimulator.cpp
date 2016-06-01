

#include "stdafx.h"
#include "LogicSimulator.h"


LogicSimulator::LogicSimulator() 
{

}

void LogicSimulator::OnePointClear(PointInfo pif)
{
	pif.input = -1;
	pif.output = -1;
	pif. and = -1;
	pif. or = -1;
	pif. xor = -1;
	pif. not = -1;
	pif.line = -1;


	pif.gatein = FALSE;
	pif.gateout = FALSE;
	
	pif.lineok = FALSE;
	pif.gate = nothing;
	pif.usingpoint = FALSE;
	int i = 0;
	pif.value = &i;
}

void LogicSimulator::AllPointClear()
{
	for (int i = 0; i < INDEX; i++)
		for (int j = 0; j < INDEX; j++)
			OnePointClear(pif[i][j]);
}

void LogicSimulator::print(LogicSimulator ls)
{
}

void LogicSimulator::create_input(Input *in, CPoint clicked)
{
	in->clicked = clicked; // 마우스가 눌린 위치.//
	in->min = { clicked.x - 1, clicked.y - 1 };
	in->max = { clicked.x + 1, clicked.y + 1 };
	in->output = { clicked.x + 1, clicked.y};

	this->pif[clicked.x][clicked.y].value = &(in->value);
	this->pif[clicked.x][clicked.y].input = this->count_input;
	this->pif[clicked.x][clicked.y].serializegate = input;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			this->pif[in->min.x + i][in->min.y + j].usingpoint = TRUE;
			this->pif[in->min.x + i][in->min.y + j].gate = input;
			this->pif[in->min.x + i][in->min.y + j].input = this->count_input;
		}
	this->pif[in->output.x][in->output.y].lineok = TRUE;
	this->pif[in->output.x][in->output.y].gateout = TRUE;
	this->pif[in->output.x][in->output.y].value = &in->value;
	/*
	for (int i = 0; i < 4; i++) {
		this->pif[in->output[i].x][in->output[i].y].lineok = TRUE;
		this->pif[in->output[i].x][in->output[i].y].gateout = TRUE;
		this->pif[in->output[i].x][in->output[i].y].value = &in->value;
	}
	*/
}

void LogicSimulator::create_output(Output *out, CPoint clicked)
{
	out->clicked = clicked;
	out->min = { clicked.x - 1, clicked.y - 1 };
	out->max = { clicked.x + 1, clicked.y + 1 };
	out->input = { clicked.x - 1, clicked.y };

	this->pif[clicked.x][clicked.y].output = this->count_output;
	this->pif[clicked.x][clicked.y].serializegate = output;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			this->pif[out->min.x + i][out->min.y + j].usingpoint = TRUE;
			this->pif[out->min.x + i][out->min.y + j].gate = output;
			this->pif[out->min.x + i][out->min.y + j].output = this->count_output;
		}
	this->pif[out->input.x][out->input.y].lineok = TRUE;
	this->pif[out->input.x][out->input.y].gatein = TRUE;
	if(this->pif[out->input.x][out->input.y].value != NULL)
		out->value = *(this->pif[out->input.x][out->input.y].value);
}

void LogicSimulator::create_and(AndGate *and, CPoint clicked) // clicked : pif 인덱스 
{
	and->clicked = clicked; //pif 인덱스
	and->min = { clicked.x-2, clicked.y-2}; // 비트맵을 찍어낼때 사용하는 left좌표
	and->max = { clicked.x+2, clicked.y+2};
	and->output = { clicked.x+2, clicked.y};//값을 내보낼 수 있는 점.
	and->input[0] = { clicked.x-2, clicked.y - 1 }; // 값을 받는 점.
	and->input[1] = { clicked.x-2, clicked.y + 1 };
	this->pif[clicked.x][clicked.y].serializegate = ::and;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				this->pif[and->min.x + i][and->min.y + j].usingpoint = TRUE;
				this->pif[and->min.x + i][and->min.y + j].gate = ::and;
				this->pif[and->min.x + i][and->min.y + j].and = this->count_and;
			}
		}
		this->pif[and->input[0].x][and->input[0].y].lineok = TRUE;
		this->pif[and->input[0].x][and->input[0].y].gatein = TRUE;
		this->pif[and->input[1].x][and->input[1].y].lineok = TRUE;
		this->pif[and->input[1].x][and->input[1].y].gatein = TRUE;
		this->pif[and->output.x][and->output.y].lineok = TRUE;
		this->pif[and->output.x][and->output.y].gateout = TRUE;
		this->pif[and->output.x][and->output.y].value = &(and ->value);

}

void LogicSimulator::SavePointOnTheLine(CPoint old_start, CPoint old_end, WhereFixed old_wherefixed) { // 그려진 선에 대한 점을 저장한다.

	CPoint tempP;
	if (old_start == old_end)
		return;

	if (old_wherefixed == GARO)
		if (old_start.y == old_end.y) { // 1줄만 그리는경우.
			 line.Add(OneLinePoint(old_start, old_end));
			 count_line++;
			 this->create_line(line.GetAt(count_line).firstPt, line.GetAt(count_line).secondPt, count_line);
			// pif[old_start.x/10][old_start.y/10].lineok = TRUE;
			// pif[old_end.x/10][old_end.y/10].lineok = TRUE;
		}

		else {//두줄을 그려줘야 하는 경우.
			tempP.x = old_end.x;
			tempP.y = old_start.y;
			 line.Add(OneLinePoint(old_start, tempP));
			 count_line++;
			 this->create_line(line.GetAt(count_line).firstPt, line.GetAt(count_line).secondPt, count_line);
			 //pif[old_start.x / 10][old_start.y / 10].lineok = TRUE;
			// pif[tempP.x / 10][tempP.y / 10].lineok = TRUE;

			tempP.x = old_end.x;
			tempP.y = old_start.y;
			 line.Add(OneLinePoint(tempP, old_end));
			 count_line++;
			 this->create_line(line.GetAt(count_line).firstPt, line.GetAt(count_line).secondPt, count_line);
			// pif[tempP.x / 10][tempP.y / 10].lineok = TRUE;
			// pif[old_end.x / 10][old_end.y / 10].lineok = TRUE;
		}
	else if (old_wherefixed == SERO) {
		if (old_start.x == old_end.x) { // 1줄만 그리는경우.
			 line.Add(OneLinePoint(old_start, old_end));
			 count_line++;
			 this->create_line(line.GetAt(count_line).firstPt, line.GetAt(count_line).secondPt, count_line);
			// pif[old_start.x / 10][old_start.y / 10].lineok = TRUE;
			// pif[old_end.x / 10][old_end.y / 10].lineok = TRUE;
		}
		else {//두줄을 그려줘야 하는 경우.
			tempP.x = old_start.x;
			tempP.y = old_end.y;
			 line.Add(OneLinePoint(old_start, tempP));
			 count_line++;
			 this->create_line(line.GetAt(count_line).firstPt, line.GetAt(count_line).secondPt, count_line);
			// pif[old_start.x / 10][old_start.y / 10].lineok = TRUE;
			// pif[tempP.x / 10][tempP.y / 10].lineok = TRUE;

			tempP.x = old_start.x;
			tempP.y = old_end.y;
			 line.Add(OneLinePoint(tempP, old_end));
			 count_line++;
			 this->create_line(line.GetAt(count_line).firstPt, line.GetAt(count_line).secondPt, count_line);
			// pif[tempP.x / 10][tempP.y / 10].lineok = TRUE;
			// pif[old_end.x / 10][old_end.y / 10].lineok = TRUE;
		}
	}
}

void LogicSimulator::create_line(CPoint firstPt, CPoint secondPt, int index) {
	// 이 함수의 주요 역할은 pif의 정보를 갱신하는 것.(저장했다가 로드 했을 때 이 정보가 있어야 연결 되므로.)
	if (firstPt.y == secondPt.y) { //가로인경우
		if ((firstPt.x - secondPt.x) < 0) {
			for (int i = 1; i <= abs(firstPt.x - secondPt.x) / 20; i++) {
				this->pif[(firstPt.x / 20) + i][firstPt.y / 20].value = pif[firstPt.x / 20][firstPt.y / 20].value;
				pif[(firstPt.x / 20) + i][firstPt.y / 20].line = index;
				pif[(firstPt.x / 20) + i][firstPt.y / 20].lineok = TRUE;
				pif[(firstPt.x / 20) + i][firstPt.y / 20].usingpoint = TRUE;
				pif[(firstPt.x / 20) + i][firstPt.y / 20].gateout = TRUE;
			}
		}
		else {
			for (int i = 1; i <= abs(firstPt.x - secondPt.x) / 20; i++) {
				pif[(firstPt.x / 20) - i][firstPt.y / 20].value = pif[firstPt.x / 20][firstPt.y / 20].value;
				pif[(firstPt.x / 20) - i][firstPt.y / 20].line = index;
				pif[(firstPt.x / 20) - i][firstPt.y / 20].lineok = TRUE;
				pif[(firstPt.x / 20) - i][firstPt.y / 20].usingpoint = TRUE;
				pif[(firstPt.x / 20) - i][firstPt.y / 20].gateout = TRUE;
			}
		}
	}
		

	else {//세로인경우
		if ((firstPt.y - secondPt.y) < 0) {
			for (int i = 1; i <= abs(firstPt.y - secondPt.y) / 20; i++) {
				pif[(firstPt.x / 20)][firstPt.y / 20 + i].value = pif[firstPt.x / 20][firstPt.y / 20].value;
				pif[(firstPt.x / 20)][firstPt.y / 20 + i].line = index;
				pif[(firstPt.x / 20)][firstPt.y / 20 + i].lineok = TRUE;
				pif[(firstPt.x / 20)][firstPt.y / 20 + i].usingpoint = TRUE;
				pif[(firstPt.x / 20)][firstPt.y / 20 + i].gateout = TRUE;
			}
		}

		else {
			for (int i = 1; i <= abs(firstPt.y - secondPt.y) / 20; i++) {
				pif[(firstPt.x / 20)][firstPt.y / 20 -i].value = pif[firstPt.x / 20][firstPt.y / 20].value;
				pif[(firstPt.x / 20)][firstPt.y / 20 - i].line = index;
				pif[(firstPt.x / 20)][firstPt.y / 20 - i].lineok = TRUE;
				pif[(firstPt.x / 20)][firstPt.y / 20 - i].usingpoint = TRUE;
				pif[(firstPt.x / 20)][firstPt.y / 20 - i].gateout = TRUE;
			}
		}
	}
}

void LogicSimulator::calculate_output(Output * out)
{
	if ( pif[out->input.x][out->input.y].value != NULL)
		 out->value = *(pif[out->input.x][out->input.y].value);
}

void LogicSimulator::calculate_xor(XorGate * xor)
{
	if (this->pif[xor->input[0].x][xor->input[0].y].value == NULL || this->pif[xor->input[1].x][xor->input[1].y].value == NULL)
		AfxMessageBox(_T("xor 선을 연결해주세요."));
	else
		if (*(this->pif[xor->input[0].x][xor->input[0].y].value) == *(this->pif[xor->input[1].x][xor->input[1].y].value))
			xor->value = 0;
		else
			xor->value = 1;
}

void LogicSimulator::calculate_nor(NorGate * nor)
{
	if (this->pif[nor->input[0].x][nor->input[0].y].value == NULL || this->pif[nor->input[1].x][nor->input[1].y].value == NULL)
		AfxMessageBox(_T("nor 선을 연결해주세요."));
	else
		if (*(this->pif[nor->input[0].x][nor->input[0].y].value) == 0 && *(this->pif[nor->input[1].x][nor->input[1].y].value) == 0)
			nor->value = 1;
		else
			nor->value = 0;
}

void LogicSimulator::calculate_or(OrGate * or )
{
	if (this->pif[or->input[0].x][or->input[0].y].value == NULL || this->pif[or->input[1].x][or->input[1].y].value == NULL)
		AfxMessageBox(_T("or 선을 연결해주세요."));
	else
		if (*(this->pif[or->input[0].x][or->input[0].y].value) == 0 && *(this->pif[or->input[1].x][or->input[1].y].value) == 0)
			or->value = 0;
		else
			or->value = 1;
}

void LogicSimulator::calculate_not(NotGate * not)
{
	if (this->pif[not->input.x][not->input.y].value == NULL)
		AfxMessageBox(_T("not 선을 연결해주세요."));
	else
		if (*(this->pif[not->input.x][not->input.y].value) == 0)
			not->value = 1;
		else
			not->value = 0;
}

void LogicSimulator::calculate_and(AndGate *and)
{
	if (this->pif[and->input[0].x][and->input[0].y].value == NULL || this->pif[and->input[1].x][and->input[1].y].value == NULL)
		if(this->pif[and->input[0].x][and->input[0].y].value == NULL)
			AfxMessageBox(_T("and 0 선을 연결해주세요."));
		else
			AfxMessageBox(_T("and 1 선을 연결해주세요."));
	else
		if (*(this->pif[and->input[0].x][and->input[0].y].value) == 1 && *(this->pif[and->input[1].x][and->input[1].y].value) == 1)
			and ->value = 1;
		else
			and->value = 0;
}

void LogicSimulator::calculate_nand(NAndGate *nand) {
	if (this->pif[nand->input[0].x][nand->input[0].y].value == NULL || this->pif[nand->input[1].x][nand->input[1].y].value == NULL)
		AfxMessageBox(_T("nand 선을 연결해주세요."));
	else
		if (*(this->pif[nand->input[0].x][nand->input[0].y].value) == 1 && *(this->pif[nand->input[1].x][nand->input[1].y].value) == 1)
			nand ->value = 0;
		else
			nand->value = 1;
}

void LogicSimulator::create_xor(XorGate * xor, CPoint clicked)
{
	xor->clicked = clicked; // 마우스가 눌린 위치.
	xor->min = { clicked.x - 2, clicked.y - 2 }; // 비트맵을 찍어낼때 사용하는 left좌표
	xor->max = { clicked.x + 2, clicked.y + 2 }; //우측하단의 점
	xor->output = { clicked.x + 2, clicked.y };//값을 내보낼 수 있는 점.
	xor->input[0] = { clicked.x - 2, clicked.y - 1 }; // 값을 받는 점.
	xor->input[1] = { clicked.x - 2, clicked.y + 1 };
	this->pif[clicked.x][clicked.y].serializegate = ::xor;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			this->pif[xor->min.x + i][xor->min.y + j].usingpoint = TRUE;
			this->pif[xor->min.x + i][xor->min.y + j].gate = ::xor;
			this->pif[xor->min.x + i][xor->min.y + j].xor = this->count_xor;
		}
	this->pif[xor->input[0].x][xor->input[0].y].lineok = TRUE;
	this->pif[xor->input[0].x][xor->input[0].y].gatein = TRUE;
	this->pif[xor->input[1].x][xor->input[1].y].lineok = TRUE;
	this->pif[xor->input[1].x][xor->input[1].y].gatein = TRUE;
	this->pif[xor->output.x][xor->output.y].lineok = TRUE;
	this->pif[xor->output.x][xor->output.y].gateout = TRUE;
	this->pif[xor->output.x][xor->output.y].value = &(xor->value);
}

void LogicSimulator::create_nor(NorGate * nor, CPoint clicked)
{
	nor->clicked = clicked; // 마우스가 눌린 위치.
	nor->min = { clicked.x - 2, clicked.y - 2 }; // 비트맵을 찍어낼때 사용하는 left좌표
	nor->max = { clicked.x + 2, clicked.y + 2 }; //우측하단의 점
	nor->output = { clicked.x + 2, clicked.y };//값을 내보낼 수 있는 점.
	nor->input[0] = { clicked.x - 2, clicked.y - 1 }; // 값을 받는 점.
	nor->input[1] = { clicked.x - 2, clicked.y + 1 };
	this->pif[clicked.x][clicked.y].serializegate = ::nor;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			this->pif[nor->min.x + i][nor->min.y + j].usingpoint = TRUE;
			this->pif[nor->min.x + i][nor->min.y + j].gate = ::nor;
			this->pif[nor->min.x + i][nor->min.y + j].nor = this->count_nor;
		}
	this->pif[nor->input[0].x][nor->input[0].y].lineok = TRUE;
	this->pif[nor->input[0].x][nor->input[0].y].gatein = TRUE;
	this->pif[nor->input[1].x][nor->input[1].y].lineok = TRUE;
	this->pif[nor->input[1].x][nor->input[1].y].gatein = TRUE;
	this->pif[nor->output.x][nor->output.y].lineok = TRUE;
	this->pif[nor->output.x][nor->output.y].gateout = TRUE;
	this->pif[nor->output.x][nor->output.y].value = &(nor->value);
}

void LogicSimulator::create_nand(NAndGate *nand, CPoint clicked) {
	nand->clicked = clicked; //pif 인덱스
	nand->min = { clicked.x - 2, clicked.y - 2 }; // 비트맵을 찍어낼때 사용하는 left좌표
	nand->max = { clicked.x + 2, clicked.y + 2 };
	nand->output = { clicked.x + 2, clicked.y };//값을 내보낼 수 있는 점.
	nand->input[0] = { clicked.x - 2, clicked.y - 1 }; // 값을 받는 점.
	nand->input[1] = { clicked.x - 2, clicked.y + 1 };
	this->pif[clicked.x][clicked.y].serializegate = ::nand;
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++) {
			this->pif[nand->min.x + i][nand->min.y + j].usingpoint = TRUE;
			this->pif[nand->min.x + i][nand->min.y + j].gate = ::nand;
			this->pif[nand->min.x + i][nand->min.y + j].nand = this->count_nand;
		}
	}
	this->pif[nand->input[0].x][nand->input[0].y].lineok = TRUE;
	this->pif[nand->input[0].x][nand->input[0].y].gatein = TRUE;
	this->pif[nand->input[1].x][nand->input[1].y].lineok = TRUE;
	this->pif[nand->input[1].x][nand->input[1].y].gatein = TRUE;
	this->pif[nand->output.x][nand->output.y].lineok = TRUE;
	this->pif[nand->output.x][nand->output.y].gateout = TRUE;
	this->pif[nand->output.x][nand->output.y].value = &(nand->value);

}

void LogicSimulator::create_or(OrGate * or , CPoint clicked)
{
	or ->clicked = clicked; // 마우스가 눌린 위치.
	or ->min = { clicked.x - 2, clicked.y - 2 };
	or ->max = { clicked.x + 2, clicked.y + 2 };
	or ->output = { clicked.x + 2, clicked.y };
	or ->input[0] = { clicked.x - 2,clicked.y - 1 };
	or ->input[1] = { clicked.x - 2, clicked.y + 1 };
	this->pif[clicked.x][clicked.y].serializegate = ::or;
	for(int i=0; i<5; i++)
		for (int j = 0; j < 5; j++) {
			this->pif[or ->min.x + i][or ->min.y + j].usingpoint = TRUE;
			this->pif[or ->min.x + i][or ->min.y + j].gate = :: or ;
			this->pif[or ->min.x + i][or ->min.y + j].or = this->count_or;
		}
	this->pif[or ->input[0].x][or ->input[0].y].lineok = TRUE;
	this->pif[or ->input[0].x][or ->input[0].y].gatein = TRUE;
	this->pif[or ->input[1].x][or ->input[1].y].lineok = TRUE;
	this->pif[or ->input[1].x][or ->input[1].y].gatein = TRUE;
	this->pif[or ->output.x][or ->output.y].lineok = TRUE;
	this->pif[or ->output.x][or ->output.y].gateout = TRUE;
	this->pif[or->output.x][or->output.y].value = &(or->value);
}

void LogicSimulator::create_not(NotGate * not, CPoint clicked)
{
	not->clicked = clicked;
	not->min = { clicked.x - 2, clicked.y - 2 };
	not->max = { clicked.x + 2, clicked.y + 2 };
	not->output = { clicked.x + 2,clicked.y };
	not->input = { clicked.x - 2,clicked.y };
	this->pif[clicked.x][clicked.y].serializegate = ::not;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			this->pif[not->min.x + i][not->min.y + j].usingpoint = TRUE;
			this->pif[not->min.x + i][not->min.y + j].gate = ::not;
			this->pif[not->min.x + i][not->min.y + j].not = this->count_not;
		}
	}

	this->pif[not->input.x][not->input.y].lineok = TRUE;
	this->pif[not->input.x][not->input.y].gatein = TRUE;
	this->pif[not->output.x][not->output.y].lineok = TRUE;
	this->pif[not->output.x][not->output.y].gateout = TRUE;
	this->pif[not->output.x][not->output.y].value = &(not->value);
}

void LogicSimulator::calculate_tff(TFF * tff)
{
	if(this->pif[tff->input.x][tff->input.y].value == NULL || this->pif[tff->clock.x][tff->clock.y].value == NULL)
		AfxMessageBox(_T("tff 선을 연결해주세요."));
	else {
		tff->newclock = *(this->pif[tff->clock.x][tff->clock.y].value);
		if (tff->trigger == TRUE) {
			if (tff->oldclock == 0 && tff->newclock == 1) {
				if (*(this->pif[tff->input.x][tff->input.y].value) == 1)
					if (tff->value == 1) {
						tff->value = 0;
						tff->value2 = 1;
					}
					else {
						tff->value = 1;
						tff->value2 = 0;
					}
			}
		}
		else {
			if (tff->oldclock == 1 && tff->newclock == 0) {
				if (*(this->pif[tff->input.x][tff->input.y].value) == 1)
					if (tff->value == 1) {
						tff->value = 0;
						tff->value2 = 1;
					}
					else {
						tff->value = 1;
						tff->value2 = 0;
					}
			}
		}
		tff->oldclock = tff->newclock;
	}
}

void LogicSimulator::calculate_jkff(JKFF * jkff) {
	if (this->pif[jkff->input[0].x][jkff->input[0].y].value == NULL || this->pif[jkff->input[1].x][jkff->input[1].y].value == NULL || this->pif[jkff->clock.x][jkff->clock.y].value == NULL)
		AfxMessageBox(_T("jkff 선을 연결해주세요."));
	else {
		jkff->newclock = *(this->pif[jkff->clock.x][jkff->clock.y].value);
		if (jkff->trigger == TRUE) {
			if (jkff->oldclock == 0 && jkff->newclock == 1) {
				if (*(this->pif[jkff->input[0].x][jkff->input[0].y].value) == 0 && *(this->pif[jkff->input[1].x][jkff->input[1].y].value) == 1)
				{
					jkff->value = 0;
					jkff->value2 = 1;
				}
				else if (*(this->pif[jkff->input[0].x][jkff->input[0].y].value) == 1 && *(this->pif[jkff->input[1].x][jkff->input[1].y].value) == 0) {
					jkff->value = 1;
					jkff->value2 = 0;
				}
				else if (*(this->pif[jkff->input[0].x][jkff->input[0].y].value) == 1 && *(this->pif[jkff->input[1].x][jkff->input[1].y].value) == 1) {
					if (jkff->value == 1) {
						jkff->value = 0;
						jkff->value2 = 1;
					}
					else {
						jkff->value = 1;
						jkff->value2 = 0;
					}
				}
			}
		}
		else {
			if (jkff->oldclock == 1 && jkff->newclock == 0) {
				if (*(this->pif[jkff->input[0].x][jkff->input[0].y].value) == 0 && *(this->pif[jkff->input[1].x][jkff->input[1].y].value) == 1)
				{
					jkff->value = 0;
					jkff->value2 = 1;
				}
				else if (*(this->pif[jkff->input[0].x][jkff->input[0].y].value) == 1 && *(this->pif[jkff->input[1].x][jkff->input[1].y].value) == 0) {
					jkff->value = 1;
					jkff->value2 = 0;
				}
				else if (*(this->pif[jkff->input[0].x][jkff->input[0].y].value) == 1 && *(this->pif[jkff->input[1].x][jkff->input[1].y].value) == 1) {
					if (jkff->value == 1) {
						jkff->value = 0;
						jkff->value2 = 1;
					}
					else {
						jkff->value = 1;
						jkff->value2 = 0;
					}
				}
			}
		}
		jkff->oldclock = jkff->newclock;
	}

}

void LogicSimulator::calculate_seg7(SEG7 * seg7) {
	if (this->pif[seg7->input[0].x][seg7->input[0].y].value == NULL || this->pif[seg7->input[1].x][seg7->input[1].y].value == NULL
		|| this->pif[seg7->input[2].x][seg7->input[2].y].value == NULL || this->pif[seg7->input[3].x][seg7->input[3].y].value == NULL
		|| this->pif[seg7->input[4].x][seg7->input[4].y].value == NULL || this->pif[seg7->input[5].x][seg7->input[5].y].value == NULL
		|| this->pif[seg7->input[6].x][seg7->input[6].y].value == NULL)
		AfxMessageBox(_T("seg7 선을 연결해주세요."));
	else
	{
		if (*(this->pif[seg7->input[0].x][seg7->input[0].y].value) == 1)
			seg7->value[0] = 1;
		else
			seg7->value[0] = 0;

		if (*(this->pif[seg7->input[1].x][seg7->input[1].y].value) == 1)
			seg7->value[1] = 1;
		else
			seg7->value[1] = 0;

		if (*(this->pif[seg7->input[2].x][seg7->input[2].y].value) == 1)
			seg7->value[2] = 1;
		else
			seg7->value[2] = 0;

		if (*(this->pif[seg7->input[3].x][seg7->input[3].y].value) == 1)
			seg7->value[3] = 1;
		else
			seg7->value[3] = 0;

		if (*(this->pif[seg7->input[4].x][seg7->input[4].y].value) == 1)
			seg7->value[4] = 1;
		else
			seg7->value[4] = 0;

		if (*(this->pif[seg7->input[5].x][seg7->input[5].y].value) == 1)
			seg7->value[5] = 1;
		else
			seg7->value[5] = 0;

		if (*(this->pif[seg7->input[6].x][seg7->input[6].y].value) == 1)
			seg7->value[6] = 1;
		else
			seg7->value[6] = 0;
	}
}

void LogicSimulator::calculate_dff(DFF * dff)
{
	if (this->pif[dff->input.x][dff->input.y].value == NULL || this->pif[dff->clock.x][dff->clock.y].value == NULL)
		AfxMessageBox(_T("dff 선을 연결해주세요."));
	else {
		dff->newclock = *(this->pif[dff->clock.x][dff->clock.y].value);
		if (dff->trigger == TRUE) {
			if (dff->oldclock == 0 && dff->newclock == 1) {
				dff->value = *(this->pif[dff->input.x][dff->input.y].value);
				if (dff->value == 0)
					dff->value2 = 1;
				else
					dff->value2 = 0;
			}
		}
		else {
			if (dff->oldclock == 1 && dff->newclock == 0) {
				dff->value = *(this->pif[dff->input.x][dff->input.y].value);
				if (dff->value == 0)
					dff->value2 = 1;
				else
					dff->value2 = 0;
			}
		}
		dff->oldclock = dff->newclock;
	}
}

void LogicSimulator::create_tff(TFF * tff, CPoint clicked)
{
	tff->clicked = clicked; // 마우스가 눌린 위치.
	tff->min = { clicked.x - 3, clicked.y - 3 };
	tff->max = { clicked.x + 3, clicked.y + 3 };
	tff->input = { clicked.x - 3, clicked.y - 1 };
	tff->clock = { clicked.x - 3, clicked.y + 1};
	tff->output[0] = { clicked.x + 3,clicked.y - 1 };
	tff->output[1] = { clicked.x + 3, clicked.y + 1 };
	this->pif[clicked.x][clicked.y].serializegate = ::tff;
	for (int i = 0; i<7; i++)
		for (int j = 0; j < 7; j++) {
			this->pif[tff->min.x + i][tff->min.y + j].usingpoint = TRUE;
			this->pif[tff->min.x + i][tff->min.y + j].gate = :: tff ;
			this->pif[tff->min.x + i][tff->min.y + j].tff = this->count_tff;
		}

	this->pif[tff->clicked.x][tff->clicked.y].tff = this->count_tff;
	this->pif[tff->input.x][tff->input.y].lineok = TRUE;
	this->pif[tff->input.x][tff->input.y].gatein = TRUE;
	this->pif[tff->clock.x][tff->clock.y].lineok = TRUE;
	this->pif[tff->clock.x][tff->clock.y].gatein = TRUE;
	this->pif[tff->output[0].x][tff->output[0].y].lineok = TRUE;
	this->pif[tff->output[0].x][tff->output[0].y].gateout = TRUE;
	this->pif[tff->output[1].x][tff->output[1].y].lineok = TRUE;
	this->pif[tff->output[1].x][tff->output[1].y].gateout = TRUE;
	this->pif[tff->output[0].x][tff->output[0].y].value = &tff->value;
	this->pif[tff->output[1].x][tff->output[1].y].value = &tff->value2;
}

void LogicSimulator::create_clock(Clock * clock, CPoint clicked)
{
	clock->clicked = clicked; // 마우스가 눌린 위치.//
						   //사각형을 그리기 위한 left와 right
	clock->min = { clicked.x - 1, clicked.y - 1 };
	clock->max = { clicked.x + 1, clicked.y + 1 };
	//값을 내보낼 수 있는 점.
	clock->output = { clicked.x + 1, clicked.y };
	this->pif[clicked.x][clicked.y].serializegate = lsclock;
	this->pif[clicked.x][clicked.y].value = &(clock->value);
	this->pif[clicked.x][clicked.y].clock = this->count_clock;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			this->pif[clock->min.x + i][clock->min.y + j].usingpoint = TRUE;
			this->pif[clock->min.x + i][clock->min.y + j].gate = lsclock;
			this->pif[clock->min.x + i][clock->min.y + j].clock = this->count_clock;
		}
	for (int i = 0; i < 4; i++) {
		this->pif[clock->output.x][clock->output.y].lineok = TRUE;
		this->pif[clock->output.x][clock->output.y].gateout = TRUE;
		this->pif[clock->output.x][clock->output.y].value = this->pif[clicked.x][clicked.y].value;
	}
}

void LogicSimulator::create_dff(DFF * dff, CPoint clicked)
{
	dff->clicked = clicked; // 마우스가 눌린 위치.
	dff->min = { clicked.x - 3, clicked.y - 3 };
	dff->max = { clicked.x + 3, clicked.y + 3 };
	dff->input = { clicked.x - 3, clicked.y - 1 };
	dff->clock = { clicked.x - 3, clicked.y + 1 };
	dff->output[0] = { clicked.x + 3,clicked.y - 1 };
	dff->output[1] = { clicked.x + 3, clicked.y + 1 };
	this->pif[clicked.x][clicked.y].serializegate = ::dff;
	for (int i = 0; i<7; i++)
		for (int j = 0; j < 7; j++) {
			this->pif[dff->min.x + i][dff->min.y + j].usingpoint = TRUE;
			this->pif[dff->min.x + i][dff->min.y + j].gate = ::dff;
			this->pif[dff->min.x + i][dff->min.y + j].dff = this->count_dff;
		}

	this->pif[dff->input.x][dff->input.y].lineok = TRUE;
	this->pif[dff->input.x][dff->input.y].gatein = TRUE;
	this->pif[dff->clock.x][dff->clock.y].lineok = TRUE;
	this->pif[dff->clock.x][dff->clock.y].gatein = TRUE;
	this->pif[dff->output[0].x][dff->output[0].y].lineok = TRUE;
	this->pif[dff->output[0].x][dff->output[0].y].gateout = TRUE;
	this->pif[dff->output[1].x][dff->output[1].y].lineok = TRUE;
	this->pif[dff->output[1].x][dff->output[1].y].gateout = TRUE;
	this->pif[dff->output[0].x][dff->output[0].y].value = &dff->value;
	this->pif[dff->output[1].x][dff->output[1].y].value = &dff->value2;
}

void LogicSimulator::create_jkff(JKFF * jkff, CPoint clicked) {
	jkff->clicked = clicked; // 마우스가 눌린 위치.
	jkff->min = { clicked.x - 3, clicked.y - 3 };
	jkff->max = { clicked.x + 3, clicked.y + 3 };
	jkff->input[0] = { clicked.x - 3, clicked.y - 2 };
	jkff->input[1] = { clicked.x - 3, clicked.y + 2 };
	jkff->clock = { clicked.x - 3, clicked.y };
	jkff->output[0] = { clicked.x + 3,clicked.y - 1 };
	jkff->output[1] = { clicked.x + 3, clicked.y + 1 };
	this->pif[clicked.x][clicked.y].serializegate = ::jkff;
	for (int i = 0; i<7; i++)
		for (int j = 0; j < 7; j++) {
			this->pif[jkff->min.x + i][jkff->min.y + j].usingpoint = TRUE;
			this->pif[jkff->min.x + i][jkff->min.y + j].gate = ::jkff;
			this->pif[jkff->min.x + i][jkff->min.y + j].jkff = this->count_jkff;
		}

	this->pif[jkff->input[0].x][jkff->input[0].y].lineok = TRUE;
	this->pif[jkff->input[0].x][jkff->input[0].y].gatein = TRUE;
	this->pif[jkff->input[1].x][jkff->input[1].y].lineok = TRUE;
	this->pif[jkff->input[1].x][jkff->input[1].y].gatein = TRUE;
	this->pif[jkff->clock.x][jkff->clock.y].lineok = TRUE;
	this->pif[jkff->clock.x][jkff->clock.y].gatein = TRUE;
	this->pif[jkff->output[0].x][jkff->output[0].y].lineok = TRUE;
	this->pif[jkff->output[0].x][jkff->output[0].y].gateout = TRUE;
	this->pif[jkff->output[1].x][jkff->output[1].y].lineok = TRUE;
	this->pif[jkff->output[1].x][jkff->output[1].y].gateout = TRUE;
	this->pif[jkff->output[0].x][jkff->output[0].y].value = &jkff->value;
	this->pif[jkff->output[1].x][jkff->output[1].y].value = &jkff->value2;
}

void LogicSimulator::create_seg7(SEG7 * seg7, CPoint clicked)
{
	seg7->clicked = clicked; // 마우스가 눌린 위치.
	seg7->min = { clicked.x - 3, clicked.y - 3 };
	seg7->max = { clicked.x + 3, clicked.y + 3 };
	seg7->input[0] = { clicked.x - 3, clicked.y - 3 };
	seg7->input[1] = { clicked.x - 3, clicked.y - 2 };
	seg7->input[2] = { clicked.x - 3, clicked.y - 1 };
	seg7->input[3] = { clicked.x - 3, clicked.y };
	seg7->input[4] = { clicked.x - 3, clicked.y + 1 };
	seg7->input[5] = { clicked.x - 3, clicked.y + 2 };
	seg7->input[6] = { clicked.x - 3, clicked.y + 3 };

	this->pif[clicked.x][clicked.y].serializegate = ::seg7;
	for (int i = 0; i<7; i++)
		for (int j = 0; j < 7; j++) {
			this->pif[seg7->min.x + i][seg7->min.y + j].usingpoint = TRUE;
			this->pif[seg7->min.x + i][seg7->min.y + j].gate = ::seg7;
			this->pif[seg7->min.x + i][seg7->min.y + j].seg7 = this->count_seg7;
			this->pif[seg7->input[i].x][seg7->input[i].y].lineok = TRUE;
			this->pif[seg7->input[i].x][seg7->input[i].y].gatein = TRUE;
		}
}

int LogicSimulator::serialize_gate(int x, int y) {
	int tempx, tempy;
	int seg = 0;
	if (pif[x][y].gate == output) {
		count_serial++;
		serial[count_serial].gate = output;
		serial[count_serial].count = pif[x][y].output;
	}
	if (pif[x][y].gate == ::seg7) {
		count_serial++;
		serial[count_serial].gate = ::seg7;
		serial[count_serial].count = pif[x][y].seg7;
		seg = 1;
	}
	if (seg == 0) {
		if (pif[x][y].line < 0) {
			AfxMessageBox(_T("run() : 선을 잘 연결해주세요."));
			return 0;
		}
		else {
			if (seg == 0)
				while (1) {
					tempx = line.GetAt(pif[x][y].line).firstPt.x;
					tempy = line.GetAt(pif[x][y].line).firstPt.y;
					x = tempx / 20;
					y = tempy / 20;
					if (this->pif[x][y].gate != nothing)
						break;
					if (this->pif[x][y].line < 0)
						return 0;
				}
		}
	}
	switch (pif[x][y].gate) {
	case input://
		return 1;
		break;
	case output://
		if (out[pif[x][y].output].serial == TRUE)
			return 1;
		else
			out[pif[x][y].output].serial = TRUE;
		count_serial++;
		serial[count_serial].count = pif[x][y].output;
		serial[count_serial].gate = output;
		serialize_gate(out[pif[x][y].output].input.x, out[pif[x][y].output].input.y);
		return 1;
	case ::and://
		if (and[pif[x][y].and].serial == TRUE)
			return 1;
		else
			and[pif[x][y].and].serial = TRUE;
		count_serial++;
		serial[count_serial].count = pif[x][y].and;
		serial[count_serial].gate = ::and;
		serialize_gate(and[pif[x][y].and].input[0].x, and[pif[x][y].and].input[0].y);
		serialize_gate(and[pif[x][y].and].input[1].x, and[pif[x][y].and].input[1].y);
		return 1;
	case ::or://
		if (or [pif[x][y]. or ].serial == TRUE)
			return 1;
		else
			or [pif[x][y]. or ].serial = TRUE;
		count_serial++;
		serial[count_serial].count = pif[x][y].or;
		serial[count_serial].gate = ::or;
		serialize_gate(or[pif[x][y].or].input[0].x, or[pif[x][y].or].input[0].y);
		serialize_gate(or[pif[x][y].or].input[1].x, or[pif[x][y].or].input[1].y);
		return 1;
	case ::xor:
		if (xor[pif[x][y]. xor].serial == TRUE)
			return 1;
		else
			xor[pif[x][y]. xor].serial = TRUE;
		count_serial++;
		serial[count_serial].count = pif[x][y].xor;
		serial[count_serial].gate = ::xor;
		serialize_gate(xor[pif[x][y].xor].input[0].x, xor[pif[x][y].xor].input[0].y);
		serialize_gate(xor[pif[x][y].xor].input[1].x, xor[pif[x][y].xor].input[1].y);
		return 1;
	case ::nand:
		if (nand[pif[x][y].nand].serial == TRUE)
			return 1;
		else
			nand[pif[x][y].nand].serial = TRUE;
		count_serial++;
		serial[count_serial].count = pif[x][y].nand;
		serial[count_serial].gate = ::nand;
		serialize_gate(nand[pif[x][y].nand].input[0].x, nand[pif[x][y].nand].input[0].y);
		serialize_gate(nand[pif[x][y].nand].input[1].x, nand[pif[x][y].nand].input[1].y);
		return 1;
	case ::nor:
		if (nor[pif[x][y].nor].serial == TRUE)
			return 1;
		else
			nor[pif[x][y].nor].serial = TRUE;
		count_serial++;
		serial[count_serial].count = pif[x][y].nor;
		serial[count_serial].gate = ::nor;
		serialize_gate(nor[pif[x][y].nor].input[0].x, nor[pif[x][y].nor].input[0].y);
		serialize_gate(nor[pif[x][y].nor].input[1].x, nor[pif[x][y].nor].input[1].y);
		return 1;
	case lsclock:
		return 1;
		break;
	case ::dff:
		if (dff[pif[x][y].dff].serial == TRUE)
			return 1;
		else
			dff[pif[x][y].dff].serial = TRUE;
		count_serial++;
		serial[count_serial].count = pif[x][y].dff;
		serial[count_serial].gate = ::dff;
		serialize_gate(dff[pif[x][y].dff].input.x, dff[pif[x][y].dff].input.y);
		serialize_gate(dff[pif[x][y].dff].clock.x, dff[pif[x][y].dff].clock.y);
		return 1;
	case ::jkff:
		if (jkff[pif[x][y].jkff].serial == TRUE)
			return 1;
		else
			jkff[pif[x][y].jkff].serial = TRUE;
		count_serial++;
		serial[count_serial].count = pif[x][y].jkff;
		serial[count_serial].gate = ::jkff;
		serialize_gate(jkff[pif[x][y].jkff].input[0].x, jkff[pif[x][y].jkff].input[0].y);
		serialize_gate(jkff[pif[x][y].jkff].input[1].x, jkff[pif[x][y].jkff].input[1].y);
		serialize_gate(jkff[pif[x][y].jkff].clock.x, jkff[pif[x][y].jkff].clock.y);
		return 1;
	case ::tff:
		if (tff[pif[x][y].tff].serial == TRUE)
			return 1;
		else
			tff[pif[x][y].tff].serial = TRUE;
		count_serial++;
		serial[count_serial].count = pif[x][y].tff;
		serial[count_serial].gate = ::tff;
		serialize_gate(tff[pif[x][y].tff].input.x, tff[pif[x][y].tff].input.y);
		serialize_gate(tff[pif[x][y].tff].clock.x, tff[pif[x][y].tff].clock.y);
		return 1;
	case ::seg7:
		if (seg7[pif[x][y].seg7].serial == TRUE)
			return 1;
		else
			seg7[pif[x][y].seg7].serial = TRUE;
		count_serial++;
		serial[count_serial].count = pif[x][y].seg7;
		serial[count_serial].gate = ::seg7;
		serialize_gate(seg7[pif[x][y].seg7].input[0].x, seg7[pif[x][y].seg7].input[0].y);
		serialize_gate(seg7[pif[x][y].seg7].input[1].x, seg7[pif[x][y].seg7].input[1].y);
		serialize_gate(seg7[pif[x][y].seg7].input[2].x, seg7[pif[x][y].seg7].input[2].y);
		serialize_gate(seg7[pif[x][y].seg7].input[3].x, seg7[pif[x][y].seg7].input[3].y);
		serialize_gate(seg7[pif[x][y].seg7].input[4].x, seg7[pif[x][y].seg7].input[4].y);
		serialize_gate(seg7[pif[x][y].seg7].input[5].x, seg7[pif[x][y].seg7].input[5].y);
		serialize_gate(seg7[pif[x][y].seg7].input[6].x, seg7[pif[x][y].seg7].input[6].y);
		return 1;
	}
}

void LogicSimulator::run(int repeat, int se[10])
{
	int end, start;
	int out = 0, se7 = 0;
	for (int a = 0; a < repeat; a++) {
		if (a == 0)
			end = se[a];
		else
			end = se[a] + 1;
		start = se[a + 1];
		for (int i = start; i >= end; i--) {
			switch (this->serial[i].gate) {
			case input://
				break;
			case output://
				out++;
				break;
			case ::and://
				this->calculate_and(&this->and[this->serial[i].count]);
				this->and[this->serial[i].count].serial = FALSE;
				break;
			case :: or ://
				this->calculate_or(&this-> or [this->serial[i].count]);
				this-> or [this->serial[i].count].serial = FALSE;
				break;
			case ::xor:
				this->calculate_xor(&this->xor[this->serial[i].count]);
				this->xor[this->serial[i].count].serial = FALSE;
				break;
			case ::nand:
				this->calculate_nand(&this->nand[this->serial[i].count]);
				this->nand[this->serial[i].count].serial = FALSE;
				break;
			case ::nor:
				this->calculate_nor(&this->nor[this->serial[i].count]);
				this->nor[this->serial[i].count].serial = FALSE;
				break;
			case lsclock:
				break;
			case ::dff:
				this->calculate_dff(&this->dff[this->serial[i].count]);
				this->dff[this->serial[i].count].serial = FALSE;
				break;
			case ::jkff:
				this->calculate_jkff(&this->jkff[this->serial[i].count]);
				this->jkff[this->serial[i].count].serial = FALSE;
				break;
			case ::tff:
				this->calculate_tff(&this->tff[this->serial[i].count]);
				this->tff[this->serial[i].count].serial = FALSE;
				break;
			case ::seg7:
				se7++;
				break;
			}
		}
	}
	for (int i = 0; i < out; i++) {
		this->calculate_output(&this->out[i]);
		this->out[this->serial[i].count].serial = FALSE;
	}
	for (int i = 0; i < se7; i++) {
		this->calculate_seg7(&this->seg7[this->serial[i].count]);
		this->seg7[this->serial[i].count].serial = FALSE;
	}
}

void LogicSimulator::rotate_and(AndGate *and, Direct dir) {
	switch (dir) {
	case LEFT:
		this->pif[and->input[0].x][and->input[0].y].lineok = FALSE;
		this->pif[and->input[0].x][and->input[0].y].gatein = FALSE;
		this->pif[and->input[1].x][and->input[1].y].lineok = FALSE;
		this->pif[and->input[1].x][and->input[1].y].gatein = FALSE;
		this->pif[and->output.x][and->output.y].lineok = FALSE;
		this->pif[and->output.x][and->output.y].gateout = FALSE;
		this->pif[and->output.x][and->output.y].value = NULL;

		and->output = { and->clicked.x - 2, and->clicked.y };//값을 내보낼 수 있는 점.
		and->input[0] = { and->clicked.x + 2, and->clicked.y - 1 }; // 값을 받는 점.
		and->input[1] = { and->clicked.x + 2, and->clicked.y + 1 };

		this->pif[and->input[0].x][and->input[0].y].lineok = TRUE;
		this->pif[and->input[0].x][and->input[0].y].gatein = TRUE;
		this->pif[and->input[1].x][and->input[1].y].lineok = TRUE;
		this->pif[and->input[1].x][and->input[1].y].gatein = TRUE;
		this->pif[and->output.x][and->output.y].lineok = TRUE;
		this->pif[and->output.x][and->output.y].gateout = TRUE;
		this->pif[and->output.x][and->output.y].value = &(and->value);
		break;
	case RIGHT:
		this->pif[and->input[0].x][and->input[0].y].lineok = FALSE;
		this->pif[and->input[0].x][and->input[0].y].gatein = FALSE;
		this->pif[and->input[1].x][and->input[1].y].lineok = FALSE;
		this->pif[and->input[1].x][and->input[1].y].gatein = FALSE;
		this->pif[and->output.x][and->output.y].lineok = FALSE;
		this->pif[and->output.x][and->output.y].gateout = FALSE;
		this->pif[and->output.x][and->output.y].value = NULL;

		and->output = { and->clicked.x + 2, and->clicked.y };//값을 내보낼 수 있는 점.
		and->input[0] = { and->clicked.x - 2, and->clicked.y - 1 }; // 값을 받는 점.
		and->input[1] = { and->clicked.x - 2, and->clicked.y + 1 };

		this->pif[and->input[0].x][and->input[0].y].lineok = TRUE;
		this->pif[and->input[0].x][and->input[0].y].gatein = TRUE;
		this->pif[and->input[1].x][and->input[1].y].lineok = TRUE;
		this->pif[and->input[1].x][and->input[1].y].gatein = TRUE;
		this->pif[and->output.x][and->output.y].lineok = TRUE;
		this->pif[and->output.x][and->output.y].gateout = TRUE;
		this->pif[and->output.x][and->output.y].value = &(and->value);
		break;
	case TOP:
		this->pif[and->input[0].x][and->input[0].y].lineok = FALSE;
		this->pif[and->input[0].x][and->input[0].y].gatein = FALSE;
		this->pif[and->input[1].x][and->input[1].y].lineok = FALSE;
		this->pif[and->input[1].x][and->input[1].y].gatein = FALSE;
		this->pif[and->output.x][and->output.y].lineok = FALSE;
		this->pif[and->output.x][and->output.y].gateout = FALSE;
		this->pif[and->output.x][and->output.y].value = NULL;

		and->output = { and->clicked.x, and->clicked.y-2 };//값을 내보낼 수 있는 점.
		and->input[0] = { and->clicked.x - 1, and->clicked.y + 2 }; // 값을 받는 점.
		and->input[1] = { and->clicked.x + 1, and->clicked.y + 2 };

		this->pif[and->input[0].x][and->input[0].y].lineok = TRUE;
		this->pif[and->input[0].x][and->input[0].y].gatein = TRUE;
		this->pif[and->input[1].x][and->input[1].y].lineok = TRUE;
		this->pif[and->input[1].x][and->input[1].y].gatein = TRUE;
		this->pif[and->output.x][and->output.y].lineok = TRUE;
		this->pif[and->output.x][and->output.y].gateout = TRUE;
		this->pif[and->output.x][and->output.y].value = &(and->value);
		break;
	case BOTTOM:
		this->pif[and->input[0].x][and->input[0].y].lineok = FALSE;
		this->pif[and->input[0].x][and->input[0].y].gatein = FALSE;
		this->pif[and->input[1].x][and->input[1].y].lineok = FALSE;
		this->pif[and->input[1].x][and->input[1].y].gatein = FALSE;
		this->pif[and->output.x][and->output.y].lineok = FALSE;
		this->pif[and->output.x][and->output.y].gateout = FALSE;
		this->pif[and->output.x][and->output.y].value = NULL;

		and->output = { and->clicked.x, and->clicked.y + 2 };//값을 내보낼 수 있는 점.
		and->input[0] = { and->clicked.x - 1, and->clicked.y - 2 }; // 값을 받는 점.
		and->input[1] = { and->clicked.x + 1, and->clicked.y - 2 };

		this->pif[and->input[0].x][and->input[0].y].lineok = TRUE;
		this->pif[and->input[0].x][and->input[0].y].gatein = TRUE;
		this->pif[and->input[1].x][and->input[1].y].lineok = TRUE;
		this->pif[and->input[1].x][and->input[1].y].gatein = TRUE;
		this->pif[and->output.x][and->output.y].lineok = TRUE;
		this->pif[and->output.x][and->output.y].gateout = TRUE;
		this->pif[and->output.x][and->output.y].value = &(and->value);
		break;
	}
}

void LogicSimulator::rotate_input(Input *in, Direct dir) {
	switch (dir) {
	case LEFT:
		this->pif[in->output.x][in->output.y].lineok = FALSE;
		this->pif[in->output.x][in->output.y].gateout = FALSE;
		this->pif[in->output.x][in->output.y].value = NULL;
		in->output = { in->clicked.x - 1, in->clicked.y };
		this->pif[in->output.x][in->output.y].lineok = TRUE;
		this->pif[in->output.x][in->output.y].gateout = TRUE;
		this->pif[in->output.x][in->output.y].value = &in->value;
		break;
	case RIGHT:
		this->pif[in->output.x][in->output.y].lineok = FALSE;
		this->pif[in->output.x][in->output.y].gateout = FALSE;
		this->pif[in->output.x][in->output.y].value = NULL;

		in->output = { in->clicked.x + 1, in->clicked.y };
		this->pif[in->output.x][in->output.y].lineok = TRUE;
		this->pif[in->output.x][in->output.y].gateout = TRUE;
		this->pif[in->output.x][in->output.y].value = &in->value;
		break;
	case TOP:
		this->pif[in->output.x][in->output.y].lineok = FALSE;
		this->pif[in->output.x][in->output.y].gateout = FALSE;
		this->pif[in->output.x][in->output.y].value = NULL;

		in->output = { in->clicked.x, in->clicked.y - 1 }; //13, 6
		this->pif[in->output.x][in->output.y].lineok = TRUE;
		this->pif[in->output.x][in->output.y].gateout = TRUE;
		this->pif[in->output.x][in->output.y].value = &in->value;
		break;
	case BOTTOM:
		this->pif[in->output.x][in->output.y].lineok = FALSE;
		this->pif[in->output.x][in->output.y].gateout = FALSE;
		this->pif[in->output.x][in->output.y].value = NULL;

		in->output = { in->clicked.x, in->clicked.y + 1 };
		this->pif[in->output.x][in->output.y].lineok = TRUE;
		this->pif[in->output.x][in->output.y].gateout = TRUE;
		this->pif[in->output.x][in->output.y].value = &in->value;
		break;
	}
}
void LogicSimulator::rotate_output(Output *out, Direct dir) {
	switch (dir) {
	case LEFT:
		this->pif[out->input.x][out->input.y].lineok = FALSE;
		this->pif[out->input.x][out->input.y].gatein = FALSE;

		out->input = { out->clicked.x-1, out->clicked.y};
		this->pif[out->input.x][out->input.y].lineok = TRUE;
		this->pif[out->input.x][out->input.y].gatein = TRUE;
		if (this->pif[out->input.x][out->input.y].value != NULL)
			out->value = *(this->pif[out->input.x][out->input.y].value);

		break;
	case RIGHT:
		this->pif[out->input.x][out->input.y].lineok = FALSE;
		this->pif[out->input.x][out->input.y].gatein = FALSE;

		out->input = { out->clicked.x + 1, out->clicked.y };
		this->pif[out->input.x][out->input.y].lineok = TRUE;
		this->pif[out->input.x][out->input.y].gatein = TRUE;
		if (this->pif[out->input.x][out->input.y].value != NULL)
			out->value = *(this->pif[out->input.x][out->input.y].value);
		break;
	case TOP:
		this->pif[out->input.x][out->input.y].lineok = FALSE;
		this->pif[out->input.x][out->input.y].gatein = FALSE;

		out->input = { out->clicked.x, out->clicked.y -1};
		this->pif[out->input.x][out->input.y].lineok = TRUE;
		this->pif[out->input.x][out->input.y].gatein = TRUE;
		if (this->pif[out->input.x][out->input.y].value != NULL)
			out->value = *(this->pif[out->input.x][out->input.y].value);
		break;
	case BOTTOM:
		this->pif[out->input.x][out->input.y].lineok = FALSE;
		this->pif[out->input.x][out->input.y].gatein = FALSE;

		out->input = { out->clicked.x, out->clicked.y+1 };
		this->pif[out->input.x][out->input.y].lineok = TRUE;
		this->pif[out->input.x][out->input.y].gatein = TRUE;
		if (this->pif[out->input.x][out->input.y].value != NULL)
			out->value = *(this->pif[out->input.x][out->input.y].value);
		break;
	}
}
