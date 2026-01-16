
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

using namespace std;


class PersistentQueue {
private:

	struct Node {
		shared_ptr<Node> next;
		shared_ptr<Node> element;

		int value;

		Node() : next(nullptr), value(0), element(nullptr) {}
		Node(shared_ptr<Node> next, int value) : next(next), value(value), element(nullptr) {}
		Node(shared_ptr<Node> next, int value, shared_ptr<Node> element) : next(next), value(value), element(element) {}
		Node(shared_ptr<Node> next, shared_ptr<Node> element) : next(next), value(0), element(element) {}
		// ~Node() {
		// 	delete next;
		// }
	};

	struct VersionInfo {
		int size;
		int ready_list_size = 0;
		int building_list_size = 0;
		shared_ptr<Node> head;
		shared_ptr<Node> tail;
		shared_ptr<Node> ready_list;
		shared_ptr<Node> building_list;

		VersionInfo(int size, shared_ptr<Node> tail, shared_ptr<Node> head) : size(size), head(head), tail(tail), ready_list(nullptr), building_list(nullptr) {}
		VersionInfo(int size, shared_ptr<Node> tail, shared_ptr<Node> head, shared_ptr<Node> ready_list, shared_ptr<Node> building_list) : size(size), head(head), tail(tail), ready_list(ready_list), building_list(building_list) {}
		// ~VersionInfo() {
		// 	delete head;
		// 	delete tail;
		// 	delete ready_list;
		// 	delete building_list;
		// }

		bool _check_ready_list() {
			if (building_list->element->next == head) {
				ready_list = building_list;
				ready_list_size = building_list_size;
				building_list = nullptr;
				building_list_size = 0;
				return true;
			}
			return false;
		}

		void maybe_build_list() {

			if (building_list == nullptr) {
				if (2 * ready_list_size >= (size - 2)) return;

				building_list = make_shared<Node>(nullptr, 0, tail->next);
				building_list_size++;
				_check_ready_list();
			} else if (!_check_ready_list()) {
				building_list = make_shared<Node>(building_list, 0, building_list->element->next);
				building_list_size++;
			}
		}
	};

	vector<shared_ptr<VersionInfo>> versions;


public:

	PersistentQueue() : versions(vector<shared_ptr<VersionInfo>>()) {
		versions.push_back(make_shared<VersionInfo>(0, nullptr, nullptr));
	}

	void push(int version, int value) {
		auto old_ = versions[version];

		// cout << value << ": ";

		auto new_ = make_shared<VersionInfo>(old_->size + 1, make_shared<Node>(old_->tail, value, nullptr), old_->head, old_->ready_list, old_->building_list);
		if (old_->size == 0) {
			new_->head = new_->tail;
		}

		new_->ready_list_size = old_->ready_list_size;
		new_->building_list_size = old_->building_list_size;
		// cout << new_->tail << '\n';
		new_->maybe_build_list();

		versions.push_back(new_);
	}

	int front(int version) {
		auto ver = versions[version];
		if (ver->size == 0) {
			throw runtime_error("front for empty queue");
		}

		return ver->head->value;
	}

	int pop(int version) {
		auto old_ = versions[version];

		if (old_->size == 0) {
			throw runtime_error("Pop for empty queue");
		} else if (old_->size == 1) {
			auto new_ = make_shared<VersionInfo>(0, nullptr, nullptr);
			versions.push_back(new_);
			return old_->tail->value;
		} else if (old_->size == 2) {
			auto new_ = make_shared<VersionInfo>(1, old_->tail, nullptr);
			versions.push_back(new_);
			return old_->head->value;
		}

		// cout << old_->ready_list << ' ' << old_->building_list_size << ' ' << old_->size << '\n';

		auto new_ = make_shared<VersionInfo>(old_->size - 1, old_->tail, old_->ready_list->element, old_->ready_list->next, old_->building_list);
		new_->ready_list_size = old_->ready_list_size - 1;
		new_->building_list_size = old_->building_list_size;
		new_->maybe_build_list();

		versions.push_back(new_);
		return old_->head->value;
	}
};


signed main() {

	auto queue = PersistentQueue();
	queue.push(0, 15);
	queue.push(1, 10);
	queue.push(2, 25);
	queue.push(3, 30);
	queue.push(4, 45);
	// queue.push(5, 50);
	queue.push(2, 4); // -> 6
	queue.push(6, 7); // -> 7
	queue.push(6, -3); // -> 8
	queue.push(7, 2); // -> 9
	queue.push(9, 10); // -> 10

	// cout << queue.pop(6) << '\n';
	// cout << queue.pop(7) << '\n';
	// cout << queue.pop(8) << '\n';
	// cout << queue.pop(9) << '\n';
	// cout << queue.pop(10) << '\n';

	cout << queue.pop(10) << '\n';
	cout << queue.pop(11) << '\n';
	cout << queue.pop(12) << '\n';
	cout << queue.pop(13) << '\n';
	cout << queue.pop(14) << '\n';
	cout << queue.pop(15) << '\n';
	// cout << queue.pop(16) << '\n';

	cout << "----------------------\n";

	cout << queue.pop(8) << '\n';
	cout << queue.pop(17) << '\n';
	cout << queue.pop(18) << '\n';
	cout << queue.pop(19) << '\n';


	return 0;
}

