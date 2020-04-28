/*
숫자가 있는 원의 정점 : Vertex
정점과 정점을 잇는 연결선 : Edge
정점의 최대 개수 30개

문제 : 정점과 정점의 연결관계가 인접행렬로 주어졌을 때 DFS를 이용하여 
시작 정점으로부터 모든 정점을 탐색한 결과를 순서대로 출력
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

#define MAX_VERTEX 30 // 정점의 최대 개수 30개로 한정 (30, 30)

int vertex; // 정점의 최대값
int map[MAX_VERTEX][MAX_VERTEX]; // 정점을 저장하는 2차원 배열
int visit[MAX_VERTEX]; // 방문한 y좌표를 마킹하기 위한 배열

void depthFirstSearch(int v) {
	visit[v] = 1;
	for (int i = 1; i <= vertex; i++) {
		// 찾는 정점이 마킹되있거나 방문하지 않았다면 
		// visit[i]에는 현재 x가 방문한 y좌표
		if (map[v][i] == 1 && !visit[i]) {
			// x가 방문한 정점 순서 출력 
			cout << i << ' ';
			// 다음 정점 탐색 
			depthFirstSearch(i); // 방문한 y좌표를 인자로 전달, 재귀 이전에 x좌표에서 재귀함수 실행(반복)
		}
	}
}

int main() {
	int T; // 테스트 케이스
	int start; // 정점 시작점
	int v1, v2; // x, y 정점

	cin >> T;

	
	for (int t = 1; t <= T; t++) {
		for (int i = 0; i < MAX_VERTEX; i++) {
			for (int j = 0; j < MAX_VERTEX; j++) {
				// 모든 마킹을 0으로 초기화
				map[i][j] = 0; 
			}
			// 모든 마킹을 0으로 초기화
			visit[i] = 0;
		}

		// 정점의 개수, 시작 정점 입력받기 
		cin >> vertex >> start;

		while (true) {
			// 정점 입력
			cin >> v1 >> v2;
			if (v1 == -1 && v2 == -1)
				break;
			map[v1][v2] = map[v2][v1] = 1;
		}
		cout << "#" << t << ' ';
		cout << start; // 첫 시작 노드 출력하고 프로그램 시작 
		depthFirstSearch(start);
		cout << endl;
	}
	return 0;
}