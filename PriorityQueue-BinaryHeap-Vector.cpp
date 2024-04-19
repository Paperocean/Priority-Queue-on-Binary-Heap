#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>

using namespace std;

// Kolejka priorytetowa na kopcu binarnym

class PriorityQueue {
private:
	vector<int> heapArray;

	int parent(int i) { return (i - 1) / 2; }
	int leftChild(int i) { return (2 * i + 1); }
	int rightChild(int i) { return (2 * i + 2); }

	void heapifyUp(int index) {
		while (index > 0 && heapArray[index] > heapArray[parent(index)]) {
			swap(heapArray[index], heapArray[parent(index)]);
			index = parent(index);
		}
	}

	void heapifyDown(int index) {
		int size = heapArray.size();
		int maxIndex = index;
		int left = leftChild(index);
		int right = rightChild(index);

		if (right < size && heapArray[right] > heapArray[maxIndex]) {
			maxIndex = right;
		}

		if (left < size && heapArray[left] > heapArray[maxIndex]) {
			maxIndex = left;
		}

		if (maxIndex != index) {
			swap(heapArray[index], heapArray[maxIndex]);
			heapifyDown(maxIndex);
		}
	}

public:
	void display() {
		for (int i = 0; i < heapArray.size(); i++) {
			cout << heapArray[i] << " ";
		}
		cout << endl;
	}

	void enqueue(int value) {
		heapArray.push_back(value);
		heapifyUp(heapArray.size() - 1);
	}

	void dequeue() {
		if (heapArray.empty()) {
			return;
		}

		heapArray[0] = heapArray.back();
		heapArray.pop_back();
		heapifyDown(0);
	}

	int peek() {
		if (!heapArray.empty())
			return heapArray[0];

		return -1;
	}

	int size() {
		return heapArray.size();
	}

	bool search(int value) {
		for (int i = 0; i < heapArray.size(); i++) {
			if (heapArray[i] == value)
				return true;
		}
		return false;
	}

	void changePriority(int index, int newPriority) {
		if (index < 0 || index >= heapArray.size())
			return;

		heapArray[index] = newPriority;
		heapifyUp(index);
		heapifyDown(index);
	}

};


auto timeMeasureAdd(PriorityQueue& obj, int value) {
	auto start = std::chrono::high_resolution_clock::now();
	obj.enqueue(value);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	return duration.count();
}
auto timeMeasureDel(PriorityQueue& obj) {
	auto start = std::chrono::high_resolution_clock::now();
	obj.dequeue();
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	return duration.count();
}
auto timeMeasureFind(PriorityQueue& obj, int value) {
	auto start = std::chrono::high_resolution_clock::now();
	obj.search(value);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	return duration.count();
}
auto timeMeasurePeek(PriorityQueue& obj) {
	auto start = std::chrono::high_resolution_clock::now();
	obj.peek(); 
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	return duration.count();
}
auto timeMeasureSize(PriorityQueue& obj) {
	auto start = std::chrono::high_resolution_clock::now();
	obj.size(); 
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	return duration.count();
}
auto timeMeasureChangePriority(PriorityQueue& obj, int index, int newPriority) {
	auto start = std::chrono::high_resolution_clock::now();
	obj.changePriority(index, newPriority); 
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	return duration.count();
}

int main() {
	vector<int> listSize = { 10, 20 , 50, 100, 200, 500, 1000 };

	for (int k = 0; k < listSize.size(); k++) {
		cout << "\nRozmiar listy: " << listSize[k] << std::endl;

		// POMIAR DODAWANIA
		int sumAdd = 0;
		for (size_t i = 0; i < 10000; i++) {
			PriorityQueue queueMeasureAdd;
			for (size_t j = 0; j < listSize[k]; j++) {
				sumAdd += timeMeasureAdd(queueMeasureAdd, 5);
			}
		}
		cout << "Sredni czas dodawania: " << ( sumAdd / 10000 ) << " nanosekund" << std::endl;

		// POMIAR USUWANIA
		int sumDel = 0;
		for (size_t i = 0; i < 10000; i++) {
			PriorityQueue queueMeasureDel;
			for (size_t j = 0; j < listSize[k]; j++) {
				queueMeasureDel.enqueue(5);
			}
			sumDel += timeMeasureDel(queueMeasureDel);
		}
		cout << "Sredni czas usuwania: " << ( sumDel / 10000 ) << " nanosekund" << std::endl;

		// POMIAR SZUKANIA
		int sumFind = 0;
		for (size_t i = 0; i < 1000; i++) {
			PriorityQueue queueMeasureFind;
			for (size_t j = 0; j < listSize[k]; j++) {
				queueMeasureFind.enqueue(j);
			}
			int num = listSize[k] / 2;
			sumFind += timeMeasureFind(queueMeasureFind, num);
		}
		cout << "Sredni czas szukania: " << sumFind / 1000 << " nanosekund" << std::endl;

		// POMIAR PODGLĄDANIA (peek)
		int sumPeek = 0;
		for (size_t i = 0; i < 10000; i++) {
			PriorityQueue queueMeasurePeek;
			for (size_t j = 0; j < listSize[k]; j++) {
				queueMeasurePeek.enqueue(j);
			}
			sumPeek += timeMeasurePeek(queueMeasurePeek);
		}
		cout << "Sredni czas podglądania: " << (sumPeek / 10000) << " nanosekund" << std::endl;

		// POMIAR ZMIANY PRIORYTETU
		int sumChangePriority = 0;
		for (size_t i = 0; i < 10000; i++) {
			PriorityQueue queueMeasureChangePriority;
			for (size_t j = 0; j < listSize[k]; j++) {
				queueMeasureChangePriority.enqueue(j);
			}
			int indexToChange = listSize[k] / 2; 
			int newPriority = 6;
			sumChangePriority += timeMeasureChangePriority(queueMeasureChangePriority, indexToChange, newPriority);
		}
		cout << "Sredni czas zmiany priorytetu: " << (sumChangePriority / 10000) << " nanosekund" << endl;
	}
}
