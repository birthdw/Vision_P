#pragma once

UINT initawsT(LPVOID pParam);				// 서버 실행
UINT ThreadSocket(LPVOID pParam);			// 소켓 통신
UINT COLORRODING(LPVOID pParam);			// 그리기 체크
UINT ThreadCamera(LPVOID pParam);			// 카메라 실행