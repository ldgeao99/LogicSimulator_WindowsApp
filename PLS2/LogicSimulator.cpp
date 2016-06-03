

#include "stdafx.h"
#include "LogicSimulator.h"


LogicSimulator::LogicSimulator() 
{

}

void LogicSimulator::OnePointClear(PointInfo *pif)
{
	pif->input = -1; //입력
	pif->output = -1; //출력
	pif->and = -1;
	pif-> or = -1;
	pif->xor = -1;
	pif->not = -1;
	pif->line = -1;
	pif->nand = -1;
	pif->nor = -1;
	pif->dff = -1;
	pif->jkff = -1;
	pif->tff = -1;
	pif->seg7 = -1;
	pif->lib = -1;
	pif->clock = -1;
	pif->dcd = -1;


	pif->gatein = FALSE; //게이트의 입력값으로 사용되는가
	pif->gateout = FALSE; //게이트의 출력값으로 사용되는가

	pif->lineok = FALSE;
	pif->gate = nothing;
	pif->serializegate = nothing;
	pif->usingpoint = FALSE;

	pif->direct = 0;

	pif->value = NULL;
}

void LogicSimulator::AllPointClear()
{
	for (int i = 0; i < INDEX; i++)
		for (int j = 0; j < INDEX; j++)
			OnePointClear(&pif[i][j]);
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

void LogicSimulator::create_lib(Library * lib, CPoint clicked){
	lib->clicked = clicked; // 마우스가 눌린 위치.
	lib->min = { clicked.x - 3, clicked.y - 3 };
	lib->max = { clicked.x + 3, clicked.y + 3 };
	lib->input[0] = { clicked.x - 3, clicked.y - 3 };
	lib->input[1] = { clicked.x - 3, clicked.y - 2 };
	lib->input[2] = { clicked.x - 3, clicked.y - 1 };
	lib->input[3] = { clicked.x - 3, clicked.y };
	lib->input[4] = { clicked.x - 3, clicked.y + 1 };
	lib->input[5] = { clicked.x - 3, clicked.y + 2 };
	lib->input[6] = { clicked.x - 3, clicked.y + 3 };
	lib->output[0] = { clicked.x + 3,clicked.y - 3 };
	lib->output[1] = { clicked.x + 3, clicked.y - 2 };
	lib->output[2] = { clicked.x + 3, clicked.y - 1 };
	lib->output[3] = { clicked.x + 3, clicked.y };
	lib->output[4] = { clicked.x + 3, clicked.y + 1 };
	lib->output[5] = { clicked.x + 3, clicked.y + 2 };
	lib->output[6] = { clicked.x + 3, clicked.y + 3 };
	this->pif[clicked.x][clicked.y].serializegate = ::lib;
	for (int i = 0; i<7; i++)
		for (int j = 0; j < 7; j++) {
			this->pif[lib->min.x + i][lib->min.y + j].usingpoint = TRUE;
			this->pif[lib->min.x + i][lib->min.y + j].gate = ::lib;
			this->pif[lib->min.x + i][lib->min.y + j].lib = this->count_lib;
		}

	this->pif[lib->clicked.x][lib->clicked.y].lib = this->count_lib;
	for (int i = 0; i < 7; i++) {
		this->pif[lib->input[i].x][lib->input[i].y].lineok = TRUE;
		this->pif[lib->input[i].x][lib->input[i].y].gatein = TRUE;
		this->pif[lib->output[i].x][lib->output[i].y].lineok = TRUE;
		this->pif[lib->output[i].x][lib->output[i].y].gateout = TRUE;
		if(lib->direct == RIGHT || lib->direct == LEFT)
			this->pif[lib->output[0].x][lib->output[i].y].value = &lib->value[i];
		else
			this->pif[lib->output[i].x][lib->output[0].y].value = &lib->value[i];
	}

}

void LogicSimulator::calculate_output(Output * out)
{
	if ( pif[out->input.x][out->input.y].value != NULL)
		 out->value = *(pif[out->input.x][out->input.y].value);
}

void LogicSimulator::calculate_xor(XorGate * xor)
{
	if (this->pif[xor->input[0].x][xor->input[0].y].value == NULL || this->pif[xor->input[1].x][xor->input[1].y].value == NULL);
		//AfxMessageBox(_T("xor 선을 연결해주세요."));
	else
		if (*(this->pif[xor->input[0].x][xor->input[0].y].value) == *(this->pif[xor->input[1].x][xor->input[1].y].value))
			xor->value = 0;
		else
			xor->value = 1;
}

void LogicSimulator::calculate_nor(NorGate * nor)
{
	if (this->pif[nor->input[0].x][nor->input[0].y].value == NULL || this->pif[nor->input[1].x][nor->input[1].y].value == NULL);
		//AfxMessageBox(_T("nor 선을 연결해주세요."));
	else
		if (*(this->pif[nor->input[0].x][nor->input[0].y].value) == 0 && *(this->pif[nor->input[1].x][nor->input[1].y].value) == 0)
			nor->value = 1;
		else
			nor->value = 0;
}

void LogicSimulator::calculate_or(OrGate * or )
{
	if (this->pif[or ->input[0].x][or ->input[0].y].value == NULL || this->pif[or ->input[1].x][or ->input[1].y].value == NULL);
		//AfxMessageBox(_T("or 선을 연결해주세요."));
	else
		if (*(this->pif[or->input[0].x][or->input[0].y].value) == 0 && *(this->pif[or->input[1].x][or->input[1].y].value) == 0)
			or->value = 0;
		else
			or->value = 1;
}

void LogicSimulator::calculate_not(NotGate * not)
{
	if (this->pif[not->input.x][not->input.y].value == NULL);
		//AfxMessageBox(_T("not 선을 연결해주세요."));
	else
		if (*(this->pif[not->input.x][not->input.y].value) == 0)
			not->value = 1;
		else
			not->value = 0;
}

void LogicSimulator::calculate_and(AndGate *and)
{
	if (this->pif[and->input[0].x][and->input[0].y].value == NULL || this->pif[and->input[1].x][and->input[1].y].value == NULL)
		if (this->pif[and->input[0].x][and->input[0].y].value == NULL);
			//AfxMessageBox(_T("and 0 선을 연결해주세요."));
		else;
			//AfxMessageBox(_T("and 1 선을 연결해주세요."));
	else
		if (*(this->pif[and->input[0].x][and->input[0].y].value) == 1 && *(this->pif[and->input[1].x][and->input[1].y].value) == 1)
			and ->value = 1;
		else
			and->value = 0;
}

void LogicSimulator::calculate_nand(NAndGate *nand) {
	if (this->pif[nand->input[0].x][nand->input[0].y].value == NULL || this->pif[nand->input[1].x][nand->input[1].y].value == NULL);
		//AfxMessageBox(_T("nand 선을 연결해주세요."));
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
	if (this->pif[tff->input.x][tff->input.y].value == NULL || this->pif[tff->clock.x][tff->clock.y].value == NULL);
		//AfxMessageBox(_T("tff 선을 연결해주세요."));
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
	if (this->pif[jkff->input[0].x][jkff->input[0].y].value == NULL || this->pif[jkff->input[1].x][jkff->input[1].y].value == NULL
		|| this->pif[jkff->clock.x][jkff->clock.y].value == NULL);
		//AfxMessageBox(_T("jkff 선을 연결해주세요."));
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
		|| this->pif[seg7->input[6].x][seg7->input[6].y].value == NULL);
		//AfxMessageBox(_T("seg7 선을 연결해주세요."));
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
	if (this->pif[dff->input.x][dff->input.y].value == NULL || this->pif[dff->clock.x][dff->clock.y].value == NULL);
		//AfxMessageBox(_T("dff 선을 연결해주세요."));
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

void LogicSimulator::calculate_lib(Library * lib, LogicSimulator *ls)
{
	int repeat = 0;
	int se[10];
	se[0] = 0;
	ls->count_serial = -1;
	for (int i = 0; i <= ls->count_input; i++) {
		if (this->pif[lib->input[i].x][lib->input[i].y].value != NULL)
			ls->in[i].value = *(this->pif[lib->input[i].x][lib->input[i].y].value);
	}
	for (int i = 0; i <= ls->count_output; i++) {
		ls->serialize_gate(ls->out[i].input.x, ls->out[i].input.y);
		repeat++;
		se[repeat] = ls->count_serial;
	}
	for (int i = 0; i <= ls->count_seg7; i++) {
		ls->serialize_gate(ls->seg7[0].clicked.x, ls->seg7[0].clicked.y);
		repeat++;
		se[repeat] = ls->count_serial;
	}
	ls->run(repeat, se, NULL);
	for (int i = 0; i <= ls->count_output; i++) {
		lib->value[i] = ls->out[i].value;
	}
}

void LogicSimulator::calculate_dcd(Decoder * dcd)
{
	int number = 0;
	if (   this->pif[dcd->input[0].x][dcd->input[0].y].value == NULL || this->pif[dcd->input[1].x][dcd->input[1].y].value == NULL
		|| this->pif[dcd->input[2].x][dcd->input[2].y].value == NULL || this->pif[dcd->input[3].x][dcd->input[3].y].value == NULL);
	else {
		if (*(this->pif[dcd->input[0].x][dcd->input[0].y].value) == 0) {
			number = number;
		}
		else {
			number = number + 8;
		}
		if (*(this->pif[dcd->input[1].x][dcd->input[1].y].value) == 0) {
			number = number;
		}
		else {
			number = number + 4;
		}
		if (*(this->pif[dcd->input[2].x][dcd->input[2].y].value) == 0) {
			number = number;
		}
		else {
			number = number + 2;
		}
		if (*(this->pif[dcd->input[3].x][dcd->input[3].y].value) == 0) {
			number = number;
		}
		else {
			number = number + 1;
		}
	}
	dcd->value[0] = 0;
	dcd->value[1] = 0;
	dcd->value[2] = 0;
	dcd->value[3] = 0;
	dcd->value[4] = 0;
	dcd->value[5] = 0;
	dcd->value[6] = 0;
	switch(number) {
		case 0:
			dcd->value[0] = 1;
			dcd->value[1] = 1;
			dcd->value[2] = 1;
			dcd->value[3] = 1;
			dcd->value[4] = 1;
			dcd->value[5] = 1;
			dcd->value[6] = 0;
			break;
		case 1:
			dcd->value[0] = 0;
			dcd->value[1] = 1;
			dcd->value[2] = 1;
			dcd->value[3] = 0;
			dcd->value[4] = 0;
			dcd->value[5] = 0;
			dcd->value[6] = 0;
			break;
		case 2:
			dcd->value[0] = 1;
			dcd->value[1] = 1;
			dcd->value[2] = 0;
			dcd->value[3] = 1;
			dcd->value[4] = 1;
			dcd->value[5] = 0;
			dcd->value[6] = 1;
			break;
		case 3:
			dcd->value[0] = 1;
			dcd->value[1] = 1;
			dcd->value[2] = 1;
			dcd->value[3] = 1;
			dcd->value[4] = 0;
			dcd->value[5] = 0;
			dcd->value[6] = 1;
			break;
		case 4:
			dcd->value[0] = 0;
			dcd->value[1] = 1;
			dcd->value[2] = 1;
			dcd->value[3] = 0;
			dcd->value[4] = 0;
			dcd->value[5] = 1;
			dcd->value[6] = 1;
			break;
		case 5:
			dcd->value[0] = 1;
			dcd->value[1] = 0;
			dcd->value[2] = 1;
			dcd->value[3] = 1;
			dcd->value[4] = 0;
			dcd->value[5] = 1;
			dcd->value[6] = 1;
			break;
		case 6:
			dcd->value[0] = 1;
			dcd->value[1] = 0;
			dcd->value[2] = 1;
			dcd->value[3] = 1;
			dcd->value[4] = 1;
			dcd->value[5] = 1;
			dcd->value[6] = 1;
			break;
		case 7:
			dcd->value[0] = 1;
			dcd->value[1] = 1;
			dcd->value[2] = 1;
			dcd->value[3] = 0;
			dcd->value[4] = 0;
			dcd->value[5] = 1;
			dcd->value[6] = 0;
			break;
		case 8:
			dcd->value[0] = 1;
			dcd->value[1] = 1;
			dcd->value[2] = 1;
			dcd->value[3] = 1;
			dcd->value[4] = 1;
			dcd->value[5] = 1;
			dcd->value[6] = 1;
			break;
		case 9:
			dcd->value[0] = 1;
			dcd->value[1] = 1;
			dcd->value[2] = 1;
			dcd->value[3] = 0;
			dcd->value[4] = 0;
			dcd->value[5] = 1;
			dcd->value[6] = 1;
			break;
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

	this->pif[clock->output.x][clock->output.y].lineok = TRUE;
	this->pif[clock->output.x][clock->output.y].gateout = TRUE;
	this->pif[clock->output.x][clock->output.y].value = this->pif[clicked.x][clicked.y].value;
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

void LogicSimulator::create_dcd(Decoder * dcd, CPoint clicked)
{
	dcd->clicked = clicked; // 마우스가 눌린 위치.
	dcd->min = { clicked.x - 3, clicked.y - 3 };
	dcd->max = { clicked.x + 3, clicked.y + 3 };
	dcd->input[0] = { clicked.x - 3, clicked.y - 3 };
	dcd->input[1] = { clicked.x - 3, clicked.y - 1 };
	dcd->input[2] = { clicked.x - 3, clicked.y + 1 };
	dcd->input[3] = { clicked.x - 3, clicked.y + 3};
	dcd->output[0] = { clicked.x + 3,clicked.y - 3 };
	dcd->output[1] = { clicked.x + 3, clicked.y - 2 };
	dcd->output[2] = { clicked.x + 3, clicked.y - 1 };
	dcd->output[3] = { clicked.x + 3, clicked.y };
	dcd->output[4] = { clicked.x + 3, clicked.y + 1 };
	dcd->output[5] = { clicked.x + 3, clicked.y + 2 };
	dcd->output[6] = { clicked.x + 3, clicked.y + 3 };
	this->pif[clicked.x][clicked.y].serializegate = ::dcd;
	for (int i = 0; i<7; i++)
		for (int j = 0; j < 7; j++) {
			this->pif[dcd->min.x + i][dcd->min.y + j].usingpoint = TRUE;
			this->pif[dcd->min.x + i][dcd->min.y + j].gate = ::dcd;
			this->pif[dcd->min.x + i][dcd->min.y + j].dcd = this->count_dcd;
		}

	this->pif[dcd->clicked.x][dcd->clicked.y].dcd = this->count_dcd;
	for (int i = 0; i < 4; i++) {
		this->pif[dcd->input[i].x][dcd->input[i].y].lineok = TRUE;
		this->pif[dcd->input[i].x][dcd->input[i].y].gatein = TRUE;
	}
	for (int i = 0; i < 7; i++) {
		this->pif[dcd->output[i].x][dcd->output[i].y].lineok = TRUE;
		this->pif[dcd->output[i].x][dcd->output[i].y].gateout = TRUE;
		this->pif[dcd->output[0].x][dcd->output[i].y].value = &dcd->value[i];
	}
}

int LogicSimulator::serialize_gate(int x, int y) {
	int tempx, tempy;
	int ou = 0;
	int seg = 0;
	if (pif[x][y].gate == output) {
		count_serial++;
		serial[count_serial].gate = output;
		serial[count_serial].count = pif[x][y].output;
		ou = 1;
	}
	if (pif[x][y].gate == ::seg7) {
		count_serial++;
		serial[count_serial].gate = ::seg7;
		serial[count_serial].count = pif[x][y].seg7;
		seg = 1;
	}

	if (this->pif[x][y].value == NULL) {
		if(ou == 1 || seg == 1)
			count_serial--;
		return 0;
	}
	else
	{
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

	
		switch (pif[x][y].gate) {
		case input:
			return 1;
		case output:
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
		case :: or ://
			if (or [pif[x][y]. or ].serial == TRUE)
				return 1;
			else
				or [pif[x][y]. or ].serial = TRUE;
			count_serial++;
			serial[count_serial].count = pif[x][y]. or ;
			serial[count_serial].gate = :: or ;
			serialize_gate(or [pif[x][y]. or ].input[0].x, or [pif[x][y]. or ].input[0].y);
			serialize_gate(or [pif[x][y]. or ].input[1].x, or [pif[x][y]. or ].input[1].y);
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
		case ::lib:
			if (lib[pif[x][y].lib].serial == TRUE)
				return 1;
			else
				lib[pif[x][y].lib].serial = TRUE;
			count_serial++;
			serial[count_serial].count = pif[x][y].lib;
			serial[count_serial].gate = ::lib;
			serialize_gate(lib[pif[x][y].lib].input[0].x, lib[pif[x][y].lib].input[0].y);
			serialize_gate(lib[pif[x][y].lib].input[1].x, lib[pif[x][y].lib].input[1].y);
			serialize_gate(lib[pif[x][y].lib].input[2].x, lib[pif[x][y].lib].input[2].y);
			serialize_gate(lib[pif[x][y].lib].input[3].x, lib[pif[x][y].lib].input[3].y);
			serialize_gate(lib[pif[x][y].lib].input[4].x, lib[pif[x][y].lib].input[4].y);
			serialize_gate(lib[pif[x][y].lib].input[5].x, lib[pif[x][y].lib].input[5].y);
			serialize_gate(lib[pif[x][y].lib].input[6].x, lib[pif[x][y].lib].input[6].y);
			return 1;
		case ::dcd:
			if (dcd[pif[x][y].dcd].serial == TRUE)
				return 1;
			else
				dcd[pif[x][y].dcd].serial = TRUE;
			count_serial++;
			serial[count_serial].count = pif[x][y].dcd;
			serial[count_serial].gate = ::dcd;
			serialize_gate(dcd[pif[x][y].dcd].input[0].x, dcd[pif[x][y].dcd].input[0].y);
			serialize_gate(dcd[pif[x][y].dcd].input[1].x, dcd[pif[x][y].dcd].input[1].y);
			serialize_gate(dcd[pif[x][y].dcd].input[2].x, dcd[pif[x][y].dcd].input[2].y);
			serialize_gate(dcd[pif[x][y].dcd].input[3].x, dcd[pif[x][y].dcd].input[3].y);
			return 1;
		}
}

void LogicSimulator::run(int repeat, int se[10], LogicSimulator *lib)
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
			case ::lib:
				this->calculate_lib(&this->lib[this->serial[i].count], lib);
				this->lib[this->serial[i].count].serial = FALSE;
				break;
			case ::dcd:
				this->calculate_dcd(&this->dcd[this->serial[i].count]);
				this->dcd[this->serial[i].count].serial = FALSE;
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
	and->direct = dir;
	this->pif[and->input[0].x][and->input[0].y].lineok = FALSE;
	this->pif[and->input[0].x][and->input[0].y].gatein = FALSE;
	this->pif[and->input[1].x][and->input[1].y].lineok = FALSE;
	this->pif[and->input[1].x][and->input[1].y].gatein = FALSE;
	this->pif[and->output.x][and->output.y].lineok = FALSE;
	this->pif[and->output.x][and->output.y].gateout = FALSE;
	this->pif[and->output.x][and->output.y].value = NULL;

	switch (dir) {
	case LEFT:
		and->output = { and->clicked.x - 2, and->clicked.y };//값을 내보낼 수 있는 점.
		and->input[0] = { and->clicked.x + 2, and->clicked.y - 1 }; // 값을 받는 점.
		and->input[1] = { and->clicked.x + 2, and->clicked.y + 1 };
		break;
	case RIGHT:
		and->output = { and->clicked.x + 2, and->clicked.y };//값을 내보낼 수 있는 점.
		and->input[0] = { and->clicked.x - 2, and->clicked.y - 1 }; // 값을 받는 점.
		and->input[1] = { and->clicked.x - 2, and->clicked.y + 1 };
		break;
	case TOP:
		and->output = { and->clicked.x, and->clicked.y-2 };//값을 내보낼 수 있는 점.
		and->input[0] = { and->clicked.x - 1, and->clicked.y + 2 }; // 값을 받는 점.
		and->input[1] = { and->clicked.x + 1, and->clicked.y + 2 };
		break;
	case BOTTOM:
		and->output = { and->clicked.x, and->clicked.y + 2 };//값을 내보낼 수 있는 점.
		and->input[0] = { and->clicked.x - 1, and->clicked.y - 2 }; // 값을 받는 점.
		and->input[1] = { and->clicked.x + 1, and->clicked.y - 2 };
		break;
	}
	this->pif[and->input[0].x][and->input[0].y].lineok = TRUE;
	this->pif[and->input[0].x][and->input[0].y].gatein = TRUE;
	this->pif[and->input[1].x][and->input[1].y].lineok = TRUE;
	this->pif[and->input[1].x][and->input[1].y].gatein = TRUE;
	this->pif[and->output.x][and->output.y].lineok = TRUE;
	this->pif[and->output.x][and->output.y].gateout = TRUE;
	this->pif[and->output.x][and->output.y].value = &(and->value);
}

void LogicSimulator::rotate_input(Input *in, Direct dir) {
	in->direct = dir;
	this->pif[in->output.x][in->output.y].lineok = FALSE;
	this->pif[in->output.x][in->output.y].gateout = FALSE;
	this->pif[in->output.x][in->output.y].value = NULL;
	switch (dir) {
	case LEFT:
		in->output = { in->clicked.x - 1, in->clicked.y };
		break;
	case RIGHT:
		in->output = { in->clicked.x + 1, in->clicked.y };
		break;
	case TOP:
		in->output = { in->clicked.x, in->clicked.y - 1 };
		break;
	case BOTTOM:
		in->output = { in->clicked.x, in->clicked.y + 1 };
		break;
	}
	this->pif[in->output.x][in->output.y].lineok = TRUE;
	this->pif[in->output.x][in->output.y].gateout = TRUE;
	this->pif[in->output.x][in->output.y].value = &in->value;
}

void LogicSimulator::rotate_output(Output *out, Direct dir) {
	out->direct = dir;
	this->pif[out->input.x][out->input.y].lineok = FALSE;
	this->pif[out->input.x][out->input.y].gatein = FALSE;

	switch (dir) {
	case LEFT:
		out->input = { out->clicked.x + 1, out->clicked.y};
		break;
	case RIGHT:
		out->input = { out->clicked.x - 1, out->clicked.y };
		break;
	case TOP:
		out->input = { out->clicked.x, out->clicked.y + 1};
		break;
	case BOTTOM:
		out->input = { out->clicked.x, out->clicked.y - 1 };
		break;
	}
	this->pif[out->input.x][out->input.y].lineok = TRUE;
	this->pif[out->input.x][out->input.y].gatein = TRUE;
	if (this->pif[out->input.x][out->input.y].value != NULL)
		out->value = *(this->pif[out->input.x][out->input.y].value);
}

void LogicSimulator::rotate_or(OrGate * or , Direct dir) {
	or ->direct = dir;
	this->pif[or ->input[0].x][or ->input[0].y].lineok = FALSE;
	this->pif[or ->input[0].x][or ->input[0].y].gatein = FALSE;
	this->pif[or ->input[1].x][or ->input[1].y].lineok = FALSE;
	this->pif[or ->input[1].x][or ->input[1].y].gatein = FALSE;
	this->pif[or ->output.x][or ->output.y].lineok = FALSE;
	this->pif[or ->output.x][or ->output.y].gateout = FALSE;
	this->pif[or ->output.x][or ->output.y].value = NULL;

	switch (dir) {
	case LEFT:
		or ->output = { or ->clicked.x - 2, or ->clicked.y };
		or ->input[0] = { or ->clicked.x + 2, or ->clicked.y - 1 };
		or ->input[1] = { or ->clicked.x + 2, or ->clicked.y + 1 };
		break;
	case RIGHT:
		or ->output = { or->clicked.x + 2, or->clicked.y };
		or ->input[0] = { or ->clicked.x - 2, or ->clicked.y - 1 };
		or ->input[1] = { or ->clicked.x - 2, or ->clicked.y + 1 };
		break;
	case TOP:
		or ->output = { or ->clicked.x, or ->clicked.y-2 };
		or ->input[0] = { or ->clicked.x - 1, or ->clicked.y + 2 };
		or ->input[1] = { or ->clicked.x + 1, or ->clicked.y + 2 };
		break;
	case BOTTOM:
		or ->output = { or ->clicked.x, or ->clicked.y + 2 };
		or ->input[0] = { or ->clicked.x - 1, or ->clicked.y - 2 };
		or ->input[1] = { or ->clicked.x + 1, or ->clicked.y - 2 };
		break;
	}
	this->pif[or ->input[0].x][or ->input[0].y].lineok = TRUE;
	this->pif[or ->input[0].x][or ->input[0].y].gatein = TRUE;
	this->pif[or ->input[1].x][or ->input[1].y].lineok = TRUE;
	this->pif[or ->input[1].x][or ->input[1].y].gatein = TRUE;
	this->pif[or ->output.x][or ->output.y].lineok = TRUE;
	this->pif[or ->output.x][or ->output.y].gateout = TRUE;
	this->pif[or ->output.x][or ->output.y].value = &or ->value;
}

void LogicSimulator::rotate_not(NotGate * not , Direct dir) {
	not->direct = dir;
	this->pif[not->input.x][not->input.y].lineok = FALSE;
	this->pif[not->input.x][not->input.y].gatein = FALSE;
	this->pif[not->output.x][not->output.y].lineok = FALSE;
	this->pif[not->output.x][not->output.y].gateout = FALSE;
	this->pif[not->output.x][not->output.y].value = NULL;

	switch (dir) {
	case LEFT:
		not->output = { not->clicked.x - 2, not->clicked.y };
		not->input = { not->clicked.x + 2, not->clicked.y };
		break;
	case RIGHT:
		not->output = { not->clicked.x + 2, not->clicked.y };
		not->input = { not->clicked.x - 2, not->clicked.y };
		break;
	case TOP:
		not->output = { not->clicked.x, not->clicked.y - 2 };
		not->input = { not->clicked.x, not->clicked.y + 2 };
		break;
	case BOTTOM:
		not->output = { not->clicked.x, not->clicked.y + 2 };
		not->input = { not->clicked.x, not->clicked.y - 2 };

		break;
	}
	this->pif[not->input.x][not->input.y].lineok = TRUE;
	this->pif[not->input.x][not->input.y].gatein = TRUE;
	this->pif[not->output.x][not->output.y].lineok = TRUE;
	this->pif[not->output.x][not->output.y].gateout = TRUE;
	this->pif[not->output.x][not->output.y].value = &(not->value);
}

void LogicSimulator::rotate_nand(NAndGate * nand , Direct dir) {
	nand->direct = dir;
	this->pif[nand->input[0].x][nand->input[0].y].lineok = FALSE;
	this->pif[nand->input[0].x][nand->input[0].y].gatein = FALSE;
	this->pif[nand->input[1].x][nand->input[1].y].lineok = FALSE;
	this->pif[nand->input[1].x][nand->input[1].y].gatein = FALSE;
	this->pif[nand->output.x][nand->output.y].lineok = FALSE;
	this->pif[nand->output.x][nand->output.y].gateout = FALSE;
	this->pif[nand->output.x][nand->output.y].value = NULL;
	switch (dir) {
	case LEFT:
		nand ->output = { nand ->clicked.x - 2, nand ->clicked.y };
		nand ->input[0] = { nand ->clicked.x + 2, nand ->clicked.y - 1 };
		nand ->input[1] = { nand ->clicked.x + 2, nand ->clicked.y + 1 };
		break;
	case RIGHT:
		nand ->output = { nand ->clicked.x + 2, nand ->clicked.y };
		nand ->input[0] = { nand ->clicked.x - 2, nand ->clicked.y - 1 };
		nand ->input[1] = { nand ->clicked.x - 2, nand ->clicked.y + 1 };
		break;
	case TOP:
		nand ->output = { nand ->clicked.x, nand ->clicked.y - 2 };
		nand ->input[0] = { nand ->clicked.x - 1, nand ->clicked.y + 2 };
		nand ->input[1] = { nand ->clicked.x + 1, nand ->clicked.y + 2 };
		break;
	case BOTTOM:
		nand ->output = { nand ->clicked.x, nand ->clicked.y + 2 };
		nand ->input[0] = { nand ->clicked.x - 1, nand ->clicked.y - 2 };
		nand ->input[1] = { nand ->clicked.x + 1, nand ->clicked.y - 2 };
		break;
	}
	this->pif[nand->input[0].x][nand->input[0].y].lineok = TRUE;
	this->pif[nand->input[0].x][nand->input[0].y].gatein = TRUE;
	this->pif[nand->input[1].x][nand->input[1].y].lineok = TRUE;
	this->pif[nand->input[1].x][nand->input[1].y].gatein = TRUE;
	this->pif[nand->output.x][nand->output.y].lineok = TRUE;
	this->pif[nand->output.x][nand->output.y].gateout = TRUE;
	this->pif[nand->output.x][nand->output.y].value = &nand->value;
}

void LogicSimulator::rotate_nor(NorGate * nor , Direct dir) {
	nor->direct = dir;
	this->pif[nor->input[0].x][nor->input[0].y].lineok = FALSE;
	this->pif[nor->input[0].x][nor->input[0].y].gatein = FALSE;
	this->pif[nor->input[1].x][nor->input[1].y].lineok = FALSE;
	this->pif[nor->input[1].x][nor->input[1].y].gatein = FALSE;
	this->pif[nor->output.x][nor->output.y].lineok = FALSE;
	this->pif[nor->output.x][nor->output.y].gateout = FALSE;
	this->pif[nor->output.x][nor->output.y].value = NULL;
	switch (dir) {
	case LEFT:
		nor ->output = { nor ->clicked.x - 2, nor ->clicked.y };
		nor ->input[0] = { nor ->clicked.x + 2, nor ->clicked.y - 1 };
		nor ->input[1] = { nor ->clicked.x + 2, nor ->clicked.y + 1 };
		break;
	case RIGHT:
		nor ->output = { nor ->clicked.x + 2, nor ->clicked.y };
		nor ->input[0] = { nor ->clicked.x - 2, nor ->clicked.y - 1 };
		nor ->input[1] = { nor ->clicked.x - 2, nor ->clicked.y + 1 };
		break;
	case TOP:
		nor ->output = { nor ->clicked.x, nor ->clicked.y - 2 };
		nor ->input[0] = { nor ->clicked.x - 1, nor ->clicked.y + 2 };
		nor ->input[1] = { nor ->clicked.x + 1, nor ->clicked.y + 2 };
		break;
	case BOTTOM:
		nor ->output = { nor ->clicked.x, nor ->clicked.y + 2 };
		nor ->input[0] = { nor ->clicked.x - 1, nor ->clicked.y - 2 };
		nor ->input[1] = { nor ->clicked.x + 1, nor ->clicked.y - 2 };
		break;
	}
	this->pif[nor->input[0].x][nor->input[0].y].lineok = TRUE;
	this->pif[nor->input[0].x][nor->input[0].y].gatein = TRUE;
	this->pif[nor->input[1].x][nor->input[1].y].lineok = TRUE;
	this->pif[nor->input[1].x][nor->input[1].y].gatein = TRUE;
	this->pif[nor->output.x][nor->output.y].lineok = TRUE;
	this->pif[nor->output.x][nor->output.y].gateout = TRUE;
	this->pif[nor->output.x][nor->output.y].value = &nor->value;
}

void LogicSimulator::rotate_xor(XorGate * xor , Direct dir) {
	xor->direct = dir;
	this->pif[xor->input[0].x][xor->input[0].y].lineok = FALSE;
	this->pif[xor->input[0].x][xor->input[0].y].gatein = FALSE;
	this->pif[xor->input[1].x][xor->input[1].y].lineok = FALSE;
	this->pif[xor->input[1].x][xor->input[1].y].gatein = FALSE;
	this->pif[xor->output.x][xor->output.y].lineok = FALSE;
	this->pif[xor->output.x][xor->output.y].gateout = FALSE;
	this->pif[xor->output.x][xor->output.y].value = NULL;
	switch (dir) {
	case LEFT:
		xor ->output = { xor ->clicked.x - 2, xor ->clicked.y };
		xor ->input[0] = { xor ->clicked.x + 2, xor ->clicked.y - 1 };
		xor ->input[1] = { xor ->clicked.x + 2, xor ->clicked.y + 1 };
		break;
	case RIGHT:
		xor ->output = { xor ->clicked.x + 2, xor ->clicked.y };
		xor ->input[0] = { xor ->clicked.x - 2, xor ->clicked.y - 1 };
		xor ->input[1] = { xor ->clicked.x - 2, xor ->clicked.y + 1 };
		break;
	case TOP:
		xor ->output = { xor ->clicked.x, xor ->clicked.y - 2 };
		xor ->input[0] = { xor ->clicked.x - 1, xor ->clicked.y + 2 };
		xor ->input[1] = { xor ->clicked.x + 1, xor ->clicked.y + 2 };
		break;
	case BOTTOM:
		xor ->output = { xor ->clicked.x, xor ->clicked.y + 2 };
		xor ->input[0] = { xor ->clicked.x - 1, xor ->clicked.y - 2 };
		xor ->input[1] = { xor ->clicked.x + 1, xor ->clicked.y - 2 };
		break;
	}
	this->pif[xor->input[0].x][xor->input[0].y].lineok = TRUE;
	this->pif[xor->input[0].x][xor->input[0].y].gatein = TRUE;
	this->pif[xor->input[1].x][xor->input[1].y].lineok = TRUE;
	this->pif[xor->input[1].x][xor->input[1].y].gatein = TRUE;
	this->pif[xor->output.x][xor->output.y].lineok = TRUE;
	this->pif[xor->output.x][xor->output.y].gateout = TRUE;
	this->pif[xor->output.x][xor->output.y].value = &xor->value;
}

void LogicSimulator::rotate_dff(DFF *dff, Direct dir) {
	dff->direct = dir;
	this->pif[dff->input.x][dff->input.y].lineok = FALSE;
	this->pif[dff->input.x][dff->input.y].gatein = FALSE;
	this->pif[dff->clock.x][dff->clock.y].lineok = FALSE;
	this->pif[dff->clock.x][dff->clock.y].gatein = FALSE;
	this->pif[dff->output[0].x][dff->output[0].y].lineok = FALSE;
	this->pif[dff->output[0].x][dff->output[0].y].gateout = FALSE;
	this->pif[dff->output[1].x][dff->output[1].y].lineok = FALSE;
	this->pif[dff->output[1].x][dff->output[1].y].gateout = FALSE;
	this->pif[dff->output[0].x][dff->output[0].y].value = NULL;
	this->pif[dff->output[1].x][dff->output[1].y].value = NULL;
	switch (dir) {
	case LEFT:
		dff->input = { dff->clicked.x + 3, dff->clicked.y + 1 };
		dff->clock = { dff->clicked.x + 3, dff->clicked.y - 1 };
		dff->output[0] = { dff->clicked.x - 3,dff->clicked.y + 1 };
		dff->output[1] = { dff->clicked.x - 3, dff->clicked.y - 1 };
		break;
	case RIGHT:
		dff->input = { dff->clicked.x - 3, dff->clicked.y - 1 };
		dff->clock = { dff->clicked.x - 3, dff->clicked.y + 1 };
		dff->output[0] = { dff->clicked.x + 3,dff->clicked.y - 1 };
		dff->output[1] = { dff->clicked.x + 3, dff->clicked.y + 1 };
		break;
	case TOP:
		dff->input = { dff->clicked.x - 1, dff->clicked.y + 3 };
		dff->clock = { dff->clicked.x + 1, dff->clicked.y + 3 };
		dff->output[0] = { dff->clicked.x - 1,dff->clicked.y - 3 };
		dff->output[1] = { dff->clicked.x + 1, dff->clicked.y - 3 };
		break;
	case BOTTOM:
		dff->input = { dff->clicked.x + 1, dff->clicked.y - 3 };
		dff->clock = { dff->clicked.x - 1, dff->clicked.y - 3 };
		dff->output[0] = { dff->clicked.x + 1,dff->clicked.y + 3 };
		dff->output[1] = { dff->clicked.x - 1, dff->clicked.y + 3 };
		break;
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

void LogicSimulator::rotate_jkff(JKFF *jkff, Direct dir) {
	jkff->direct = dir;
	this->pif[jkff->input[0].x][jkff->input[0].y].lineok = FALSE;
	this->pif[jkff->input[0].x][jkff->input[0].y].gatein = FALSE;
	this->pif[jkff->input[1].x][jkff->input[1].y].lineok = FALSE;
	this->pif[jkff->input[1].x][jkff->input[1].y].gatein = FALSE;
	this->pif[jkff->clock.x][jkff->clock.y].lineok = FALSE;
	this->pif[jkff->clock.x][jkff->clock.y].gatein = FALSE;
	this->pif[jkff->output[0].x][jkff->output[0].y].lineok = FALSE;
	this->pif[jkff->output[0].x][jkff->output[0].y].gateout = FALSE;
	this->pif[jkff->output[1].x][jkff->output[1].y].lineok = FALSE;
	this->pif[jkff->output[1].x][jkff->output[1].y].gateout = FALSE;
	this->pif[jkff->output[0].x][jkff->output[0].y].value = NULL;
	this->pif[jkff->output[1].x][jkff->output[1].y].value = NULL;

	switch (dir) {
	case LEFT:
		jkff->input[0] = { jkff->clicked.x + 3, jkff->clicked.y - 2 };
		jkff->input[1] = { jkff->clicked.x + 3, jkff->clicked.y + 2 };
		jkff->clock = { jkff->clicked.x + 3, jkff->clicked.y };
		jkff->output[0] = { jkff->clicked.x - 3, jkff->clicked.y - 1 };
		jkff->output[1] = { jkff->clicked.x - 3, jkff->clicked.y + 1 };
		break;
	case RIGHT:
		jkff->input[0] = { jkff->clicked.x - 3, jkff->clicked.y - 2 };
		jkff->input[1] = { jkff->clicked.x - 3, jkff->clicked.y + 2 };
		jkff->clock = { jkff->clicked.x - 3, jkff->clicked.y };
		jkff->output[0] = { jkff->clicked.x + 3, jkff->clicked.y - 1 };
		jkff->output[1] = { jkff->clicked.x + 3, jkff->clicked.y + 1 };
		break;
	case TOP:
		jkff->input[0] = { jkff->clicked.x - 2, jkff->clicked.y + 3 };
		jkff->input[1] = { jkff->clicked.x + 2, jkff->clicked.y + 3 };
		jkff->clock = { jkff->clicked.x, jkff->clicked.y +3};
		jkff->output[0] = { jkff->clicked.x - 1, jkff->clicked.y - 3 };
		jkff->output[1] = { jkff->clicked.x + 1, jkff->clicked.y - 3 };
		break;
	case BOTTOM:
		jkff->input[0] = { jkff->clicked.x - 2, jkff->clicked.y - 3 };
		jkff->input[1] = { jkff->clicked.x + 2, jkff->clicked.y - 3 };
		jkff->clock = { jkff->clicked.x, jkff->clicked.y - 3 };
		jkff->output[0] = { jkff->clicked.x - 1, jkff->clicked.y + 3 };
		jkff->output[1] = { jkff->clicked.x + 1, jkff->clicked.y + 3 };
		break;
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

void LogicSimulator::rotate_tff(TFF *tff, Direct dir) {
	tff->direct = dir;
	this->pif[tff->input.x][tff->input.y].lineok = FALSE;
	this->pif[tff->input.x][tff->input.y].gatein = FALSE;
	this->pif[tff->clock.x][tff->clock.y].lineok = FALSE;
	this->pif[tff->clock.x][tff->clock.y].gatein = FALSE;
	this->pif[tff->output[0].x][tff->output[0].y].lineok = FALSE;
	this->pif[tff->output[0].x][tff->output[0].y].gateout = FALSE;
	this->pif[tff->output[1].x][tff->output[1].y].lineok = FALSE;
	this->pif[tff->output[1].x][tff->output[1].y].gateout = FALSE;
	this->pif[tff->output[0].x][tff->output[0].y].value = NULL;
	this->pif[tff->output[1].x][tff->output[1].y].value = NULL;

	switch (dir) {
	case LEFT:
		tff->input = { tff->clicked.x + 3, tff->clicked.y + 1 };
		tff->clock = { tff->clicked.x + 3, tff->clicked.y - 1 };
		tff->output[0] = { tff->clicked.x - 3,tff->clicked.y + 1 };
		tff->output[1] = { tff->clicked.x - 3, tff->clicked.y - 1 };
		break;
	case RIGHT:
		tff->input = { tff->clicked.x - 3, tff->clicked.y - 1 };
		tff->clock = { tff->clicked.x - 3, tff->clicked.y + 1 };
		tff->output[0] = { tff->clicked.x + 3,tff->clicked.y - 1 };
		tff->output[1] = { tff->clicked.x + 3, tff->clicked.y + 1 };
		break;
	case TOP:
		tff->input = { tff->clicked.x - 1, tff->clicked.y + 3 };
		tff->clock = { tff->clicked.x + 1, tff->clicked.y + 3 };
		tff->output[0] = { tff->clicked.x - 1,tff->clicked.y - 3 };
		tff->output[1] = { tff->clicked.x + 1, tff->clicked.y - 3 };
		break;
	case BOTTOM:
		tff->input = { tff->clicked.x + 1, tff->clicked.y - 3 };
		tff->clock = { tff->clicked.x - 1, tff->clicked.y - 3 };
		tff->output[0] = { tff->clicked.x + 1,tff->clicked.y + 3 };
		tff->output[1] = { tff->clicked.x - 1, tff->clicked.y + 3 };
		break;
	}
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

void LogicSimulator::rotate_clock(Clock *clock, Direct dir) {
	clock->direct = dir;

	this->pif[clock->output.x][clock->output.y].lineok = FALSE;
	this->pif[clock->output.x][clock->output.y].gateout = FALSE;
	this->pif[clock->clicked.x][clock->clicked.y].value = NULL;
	this->pif[clock->output.x][clock->output.y].value = NULL;
	switch (dir) {
	case LEFT:
		clock->output = { clock->clicked.x - 1, clock->clicked.y };
		break;
	case RIGHT:
		clock->output = { clock->clicked.x + 1, clock->clicked.y };
		break;
	case TOP:
		clock->output = { clock->clicked.x, clock->clicked.y-1 };
		break;
	case BOTTOM:
		clock->output = { clock->clicked.x, clock->clicked.y+1 };
		break;
	}
	this->pif[clock->output.x][clock->output.y].lineok = TRUE;
	this->pif[clock->output.x][clock->output.y].gateout = TRUE;
	this->pif[clock->clicked.x][clock->clicked.y].value = &(clock->value);
	this->pif[clock->output.x][clock->output.y].value = this->pif[clock->clicked.x][clock->clicked.y].value;
}

void LogicSimulator::rotate_seg7(SEG7 *seg7, Direct dir) {
	seg7->direct = dir;
	for (int i = 0; i<7; i++)
		for (int j = 0; j < 7; j++) {
			this->pif[seg7->input[i].x][seg7->input[i].y].lineok = FALSE;
			this->pif[seg7->input[i].x][seg7->input[i].y].gatein = FALSE;
		}
	switch (dir) {
	case LEFT:
		seg7->input[0] = { seg7->clicked.x + 3, seg7->clicked.y - 3 };
		seg7->input[1] = { seg7->clicked.x + 3, seg7->clicked.y - 2 };
		seg7->input[2] = { seg7->clicked.x + 3, seg7->clicked.y - 1 };
		seg7->input[3] = { seg7->clicked.x + 3, seg7->clicked.y };
		seg7->input[4] = { seg7->clicked.x + 3, seg7->clicked.y + 1 };
		seg7->input[5] = { seg7->clicked.x + 3, seg7->clicked.y + 2 };
		seg7->input[6] = { seg7->clicked.x + 3, seg7->clicked.y + 3 };
		break;
	case RIGHT:
		seg7->input[0] = { seg7->clicked.x - 3, seg7->clicked.y - 3 };
		seg7->input[1] = { seg7->clicked.x - 3, seg7->clicked.y - 2 };
		seg7->input[2] = { seg7->clicked.x - 3, seg7->clicked.y - 1 };
		seg7->input[3] = { seg7->clicked.x - 3, seg7->clicked.y };
		seg7->input[4] = { seg7->clicked.x - 3, seg7->clicked.y + 1 };
		seg7->input[5] = { seg7->clicked.x - 3, seg7->clicked.y + 2 };
		seg7->input[6] = { seg7->clicked.x - 3, seg7->clicked.y + 3 };
		break;
	case TOP:
		seg7->input[0] = { seg7->clicked.x - 3, seg7->clicked.y - 3 };
		seg7->input[1] = { seg7->clicked.x - 2, seg7->clicked.y - 3 };
		seg7->input[2] = { seg7->clicked.x - 1, seg7->clicked.y - 3 };
		seg7->input[3] = { seg7->clicked.x, seg7->clicked.y - 3 };
		seg7->input[4] = { seg7->clicked.x + 1, seg7->clicked.y - 3 };
		seg7->input[5] = { seg7->clicked.x + 2, seg7->clicked.y - 3 };
		seg7->input[6] = { seg7->clicked.x + 3, seg7->clicked.y - 3 };
		break;
	case BOTTOM:
		seg7->input[0] = { seg7->clicked.x - 3, seg7->clicked.y + 3 };
		seg7->input[1] = { seg7->clicked.x - 2, seg7->clicked.y + 3 };
		seg7->input[2] = { seg7->clicked.x - 1, seg7->clicked.y + 3 };
		seg7->input[3] = { seg7->clicked.x, seg7->clicked.y + 3 };
		seg7->input[4] = { seg7->clicked.x + 1, seg7->clicked.y + 3 };
		seg7->input[5] = { seg7->clicked.x + 2, seg7->clicked.y + 3 };
		seg7->input[6] = { seg7->clicked.x + 3, seg7->clicked.y + 3 };
		break;
	}

	for (int i = 0; i<7; i++)
		for (int j = 0; j < 7; j++) {
			this->pif[seg7->input[i].x][seg7->input[i].y].lineok = TRUE;
			this->pif[seg7->input[i].x][seg7->input[i].y].gatein = TRUE;
		}
}

void LogicSimulator::rotate_lib(Library *lib, Direct dir) {
	for (int i = 0; i < 7; i++) {
		this->pif[lib->input[i].x][lib->input[i].y].lineok = FALSE;
		this->pif[lib->input[i].x][lib->input[i].y].gatein = FALSE;
		this->pif[lib->output[i].x][lib->output[i].y].lineok = FALSE;
		this->pif[lib->output[i].x][lib->output[i].y].gateout = FALSE;
		this->pif[lib->output[0].x][lib->output[i].y].value = NULL;
	}
	switch (dir) {
	case LEFT:
		lib->input[0] = { lib->clicked.x + 3, lib->clicked.y - 3 };
		lib->input[1] = { lib->clicked.x + 3, lib->clicked.y - 2 };
		lib->input[2] = { lib->clicked.x + 3, lib->clicked.y - 1 };
		lib->input[3] = { lib->clicked.x + 3, lib->clicked.y };
		lib->input[4] = { lib->clicked.x + 3, lib->clicked.y + 1 };
		lib->input[5] = { lib->clicked.x + 3, lib->clicked.y + 2 };
		lib->input[6] = { lib->clicked.x + 3, lib->clicked.y + 3 };
		lib->output[0] = { lib->clicked.x - 3, lib->clicked.y - 3 };
		lib->output[1] = { lib->clicked.x - 3, lib->clicked.y - 2 };
		lib->output[2] = { lib->clicked.x - 3, lib->clicked.y - 1 };
		lib->output[3] = { lib->clicked.x - 3, lib->clicked.y };
		lib->output[4] = { lib->clicked.x - 3, lib->clicked.y + 1 };
		lib->output[5] = { lib->clicked.x - 3, lib->clicked.y + 2 };
		lib->output[6] = { lib->clicked.x - 3, lib->clicked.y + 3 };
		break;
	case RIGHT:
		lib->input[0] = { lib->clicked.x - 3, lib->clicked.y - 3 };
		lib->input[1] = { lib->clicked.x - 3, lib->clicked.y - 2 };
		lib->input[2] = { lib->clicked.x - 3, lib->clicked.y - 1 };
		lib->input[3] = { lib->clicked.x - 3, lib->clicked.y };
		lib->input[4] = { lib->clicked.x - 3, lib->clicked.y + 1 };
		lib->input[5] = { lib->clicked.x - 3, lib->clicked.y + 2 };
		lib->input[6] = { lib->clicked.x - 3, lib->clicked.y + 3 };
		lib->output[0] = { lib->clicked.x + 3, lib->clicked.y - 3 };
		lib->output[1] = { lib->clicked.x + 3, lib->clicked.y - 2 };
		lib->output[2] = { lib->clicked.x + 3, lib->clicked.y - 1 };
		lib->output[3] = { lib->clicked.x + 3, lib->clicked.y };
		lib->output[4] = { lib->clicked.x + 3, lib->clicked.y + 1 };
		lib->output[5] = { lib->clicked.x + 3, lib->clicked.y + 2 };
		lib->output[6] = { lib->clicked.x + 3, lib->clicked.y + 3 };
		break;
	case TOP:
		lib->input[0] = { lib->clicked.x - 3, lib->clicked.y + 3 };
		lib->input[1] = { lib->clicked.x - 2, lib->clicked.y + 3 };
		lib->input[2] = { lib->clicked.x - 1, lib->clicked.y + 3 };
		lib->input[3] = { lib->clicked.x, lib->clicked.y + 3 };
		lib->input[4] = { lib->clicked.x + 1, lib->clicked.y + 3 };
		lib->input[5] = { lib->clicked.x + 2, lib->clicked.y + 3 };
		lib->input[6] = { lib->clicked.x + 3, lib->clicked.y + 3 };
		lib->output[0] = { lib->clicked.x - 3, lib->clicked.y - 3 };
		lib->output[1] = { lib->clicked.x - 2, lib->clicked.y - 3 };
		lib->output[2] = { lib->clicked.x - 1, lib->clicked.y - 3 };
		lib->output[3] = { lib->clicked.x , lib->clicked.y - 3 };
		lib->output[4] = { lib->clicked.x + 1, lib->clicked.y - 3 };
		lib->output[5] = { lib->clicked.x + 2, lib->clicked.y - 3 };
		lib->output[6] = { lib->clicked.x + 3, lib->clicked.y - 3 };
		break;
	case BOTTOM:
		lib->input[0] = { lib->clicked.x - 3, lib->clicked.y - 3 };
		lib->input[1] = { lib->clicked.x - 2, lib->clicked.y - 3 };
		lib->input[2] = { lib->clicked.x - 1, lib->clicked.y - 3 };
		lib->input[3] = { lib->clicked.x, lib->clicked.y - 3 };
		lib->input[4] = { lib->clicked.x + 1, lib->clicked.y - 3 };
		lib->input[5] = { lib->clicked.x + 2, lib->clicked.y - 3 };
		lib->input[6] = { lib->clicked.x + 3, lib->clicked.y - 3 };
		lib->output[0] = { lib->clicked.x - 3, lib->clicked.y + 3 };
		lib->output[1] = { lib->clicked.x - 2, lib->clicked.y + 3 };
		lib->output[2] = { lib->clicked.x - 1, lib->clicked.y + 3 };
		lib->output[3] = { lib->clicked.x , lib->clicked.y + 3 };
		lib->output[4] = { lib->clicked.x + 1, lib->clicked.y + 3 };
		lib->output[5] = { lib->clicked.x + 2, lib->clicked.y + 3 };
		lib->output[6] = { lib->clicked.x + 3, lib->clicked.y + 3 };
		break;
	}
	for (int i = 0; i < 7; i++) {
		this->pif[lib->input[i].x][lib->input[i].y].lineok = TRUE;
		this->pif[lib->input[i].x][lib->input[i].y].gatein = TRUE;
		this->pif[lib->output[i].x][lib->output[i].y].lineok = TRUE;
		this->pif[lib->output[i].x][lib->output[i].y].gateout = TRUE;

		if (lib->direct == RIGHT || lib->direct == LEFT)
			this->pif[lib->output[0].x][lib->output[i].y].value = &lib->value[i];
		else
			this->pif[lib->output[i].x][lib->output[0].y].value = &lib->value[i];
	}
}

void LogicSimulator::lsdelete(CPoint p1)
{
	int x = p1.x / 20;
	int y = p1.y / 20;
	CPoint clicked = { x, y };
	int num = 0;
	WhatGate gate;
	switch (this->pif[x][y].gate) {
	case ::input: //입력
		num = this->pif[x][y].input;
		gate = ::input;
		break;
	case ::output://출력
		num = this->pif[x][y].output;
		gate = ::output;
		break;
	case ::lsclock:
		num = this->pif[x][y].clock;
		gate = ::lsclock;
		break;
	case ::and:
		num = this->pif[x][y].and;
		gate = ::and;
		break;
	case :: or :
		num = this->pif[x][y]. or ;
		gate = :: or ;
		break;
	case ::xor:
		num = this->pif[x][y].xor;
		gate = ::xor;
		break;
	case ::not:
		num = this->pif[x][y].not;
		gate = ::not;
		break;
	case ::nand:
		num = this->pif[x][y].nand;
		gate = ::nand;
		break;
	case ::nor:
		num = this->pif[x][y].nor;
		gate = ::nor;
		break;
	case ::dff:
		num = this->pif[x][y].dff;
		gate = ::dff;
		break;
	case ::jkff:
		num = this->pif[x][y].jkff;
		gate = ::jkff;
		break;
	case ::tff:
		num = this->pif[x][y].tff;
		gate = ::tff;
		break;

	case ::seg7:
		num = this->pif[x][y].seg7;
		gate = ::seg7;
		break;
	case ::lib:
		num = this->pif[x][y].lib;
		gate = ::lib;
		break;
	case ::dcd:
		num = this->pif[x][y].dcd;
		gate = ::dcd;
		break;
	default:
		if (this->pif[x][y].line >= 0) {
			num = this->pif[x][y].line;
			gate = ::line;
		}
		break;
	}

	switch (gate) {
	case ::input: //입력
		for (int i =  -1; i < 2; i++) {
			for (int j =  - 1; j < 2; j++) {
				this->OnePointClear(&this->pif[clicked.x + i][clicked.y + j]);
			}
		}
		this->in[num].clicked.x = 0;
		this->in[num].clicked.y = 0;
		break;
	case ::output://출력
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				this->OnePointClear(&this->pif[clicked.x + i][clicked.y + j]);
			}
		}
		this->out[num].clicked.x = 0;
		this->out[num].clicked.y = 0;
		break;
	case ::lsclock:
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				this->OnePointClear(&this->pif[clicked.x + i][clicked.y + j]);
			}
		}
		this->clock[num].clicked.x = 0;
		this->clock[num].clicked.y = 0;
		break;
	case ::and:
		for (int i = -2; i < 3; i++) {
			for (int j = -2; j < 3; j++) {
				this->OnePointClear(&this->pif[clicked.x + i][clicked.y + j]);
			}
		}
		this->and[num].clicked.x = 0;
		this->and[num].clicked.y = 0;
		break;
	case ::or:
		for (int i = -2; i < 3; i++) {
			for (int j = -2; j < 3; j++) {
				this->OnePointClear(&this->pif[clicked.x + i][clicked.y + j]);
			}
		}
		this-> or [num].clicked.x = 0;
		this-> or [num].clicked.y = 0;
		break;
	case ::xor:
		for (int i = -2; i < 3; i++) {
			for (int j = -2; j < 3; j++) {
				this->OnePointClear(&this->pif[clicked.x + i][clicked.y + j]);
			}
		}
		this->xor[num].clicked.x = 0;
		this->xor[num].clicked.y = 0;
		break;
	case ::not:
		for (int i = -2; i < 3; i++) {
			for (int j = -2; j < 3; j++) {
				this->OnePointClear(&this->pif[clicked.x + i][clicked.y + j]);
			}
		}
		this->not[num].clicked.x = 0;
		this->not[num].clicked.y = 0;
		break;
	case ::nand:
		for (int i = -2; i < 3; i++) {
			for (int j = -2; j < 3; j++) {
				this->OnePointClear(&this->pif[clicked.x + i][clicked.y + j]);
			}
		}
		this->nand[num].clicked.x = 0;
		this->nand[num].clicked.y = 0;
		break;
	case ::nor:
		for (int i = -2; i < 3; i++) {
			for (int j = -2; j < 3; j++) {
				this->OnePointClear(&this->pif[clicked.x + i][clicked.y + j]);
			}
		}
		this->nor[num].clicked.x = 0;
		this->nor[num].clicked.y = 0;
		break;
	case ::dff:
		for (int i = -2; i < 3; i++) {
			for (int j = -2; j < 3; j++) {
				this->OnePointClear(&this->pif[clicked.x + i][clicked.y + j]);
			}
		}
		this->dff[num].clicked.x = 0;
		this->dff[num].clicked.y = 0;
		break;
	case ::jkff:
		for (int i = -2; i < 3; i++) {
			for (int j = -2; j < 3; j++) {
				this->OnePointClear(&this->pif[clicked.x + i][clicked.y + j]);
			}
		}
		this->jkff[num].clicked.x = 0;
		this->jkff[num].clicked.y = 0;
		break;
	case ::tff:
		for (int i = -2; i < 3; i++) {
			for (int j = -2; j < 3; j++) {
				this->OnePointClear(&this->pif[clicked.x + i][clicked.y + j]);
			}
		}
		this->tff[num].clicked.x = 0;
		this->tff[num].clicked.y = 0;
		break;

	case ::seg7:
		for (int i = -3; i < 4; i++) {
			for (int j = -3; j < 4; j++) {
				this->OnePointClear(&this->pif[clicked.x + i][clicked.y + j]);
			}
		}
		this->seg7[num].clicked.x = 0;
		this->seg7[num].clicked.y = 0;
		break;
	case ::lib: 
		for (int i = -3; i < 4; i++) {
			for (int j = -3; j < 4; j++) {
				this->OnePointClear(&this->pif[clicked.x + i][clicked.y + j]);
			}
		}
		this->lib[num].clicked.x = 0;
		this->lib[num].clicked.y = 0;
		break;
	case ::dcd :
		for (int i = -3; i < 4; i++) {
			for (int j = -3; j < 4; j++) {
				this->OnePointClear(&this->pif[clicked.x + i][clicked.y + j]);
			}
		}
		this->dcd[num].clicked.x = 0;
		this->dcd[num].clicked.y = 0;
		break;
	case ::line:
		CPoint s, e;
		s = this->line[num].firstPt;
		e = this->line[num].secondPt;
		int i, j;
		if (s.x == e.x) {
			if (s.y > e.y) {
				i = (s.y - e.y) / 20;
				for (j = 1; j < i; j++) {
					this->OnePointClear(&this->pif[s.x / 20][s.y / 20 - j]);
				}
				this->pif[s.x / 20][s.y / 20 - j].gateout = FALSE;
			}
			else {
				i = (e.y - s.y) / 20;
				for (j = 1; j < i; j++) {
					this->OnePointClear(&this->pif[s.x / 20][s.y / 20 + j]);
				}
				this->pif[s.x / 20][s.y / 20 + j].gateout = FALSE;
			}

		}
		else {
			if (s.x > e.x) {
				i = (s.x - e.x) / 20;
				for (j = 1; j < i; j++) {
					this->OnePointClear(&this->pif[s.x / 20 - j][s.y / 20]);
				}
				this->pif[s.x / 20 - j][s.y / 20].gateout = FALSE;
			}
			else {
				i = (e.x - s.x) / 20;
				for (j = 1; j < i; j++) {
					this->OnePointClear(&this->pif[s.x / 20 + j][s.y / 20]);
				}
				this->pif[s.x / 20 + j][s.y / 20].gateout = FALSE;
			}
		}

		this->line[num].firstPt.x = 0;
		this->line[num].firstPt.y = 0;
		this->line[num].secondPt.x = 0;
		this->line[num].secondPt.y = 0;
		break;
	}
}
