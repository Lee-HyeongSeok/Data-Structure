/*
���ڰ� �ִ� ���� ���� : Vertex
������ ������ �մ� ���ἱ : Edge
������ �ִ� ���� 30��

���� : ������ ������ ������谡 ������ķ� �־����� �� DFS�� �̿��Ͽ� 
���� �������κ��� ��� ������ Ž���� ����� ������� ���
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

#define MAX_VERTEX 30 // ������ �ִ� ���� 30���� ���� (30, 30)

int vertex; // ������ �ִ밪
int map[MAX_VERTEX][MAX_VERTEX]; // ������ �����ϴ� 2���� �迭
int visit[MAX_VERTEX]; // �湮�� y��ǥ�� ��ŷ�ϱ� ���� �迭

void depthFirstSearch(int v) {
	visit[v] = 1;
	for (int i = 1; i <= vertex; i++) {
		// ã�� ������ ��ŷ���ְų� �湮���� �ʾҴٸ� 
		// visit[i]���� ���� x�� �湮�� y��ǥ
		if (map[v][i] == 1 && !visit[i]) {
			// x�� �湮�� ���� ���� ��� 
			cout << i << ' ';
			// ���� ���� Ž�� 
			depthFirstSearch(i); // �湮�� y��ǥ�� ���ڷ� ����, ��� ������ x��ǥ���� ����Լ� ����(�ݺ�)
		}
	}
}

int main() {
	int T; // �׽�Ʈ ���̽�
	int start; // ���� ������
	int v1, v2; // x, y ����

	cin >> T;

	
	for (int t = 1; t <= T; t++) {
		for (int i = 0; i < MAX_VERTEX; i++) {
			for (int j = 0; j < MAX_VERTEX; j++) {
				// ��� ��ŷ�� 0���� �ʱ�ȭ
				map[i][j] = 0; 
			}
			// ��� ��ŷ�� 0���� �ʱ�ȭ
			visit[i] = 0;
		}

		// ������ ����, ���� ���� �Է¹ޱ� 
		cin >> vertex >> start;

		while (true) {
			// ���� �Է�
			cin >> v1 >> v2;
			if (v1 == -1 && v2 == -1)
				break;
			map[v1][v2] = map[v2][v1] = 1;
		}
		cout << "#" << t << ' ';
		cout << start; // ù ���� ��� ����ϰ� ���α׷� ���� 
		depthFirstSearch(start);
		cout << endl;
	}
	return 0;
}