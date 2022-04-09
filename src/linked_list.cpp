#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* node = new Node(value);
    size_ += 1;
    if (IsEmpty()) {
      front_ = node;
      back_ = node;
      return;
    }
    back_->next = node;
    back_ = node;
  }

  bool LinkedList::Insert(int index, int value) {

    if (index < 0 || index > size_) {
      return false;
    }
    auto* node = new Node(value);

    if (front_ == nullptr) {
      front_ = node;
      back_ = node;
    } else {
      if (index == 0) {
        node->next = front_;
        front_ = node;
      } else if (index == size_) {
        back_->next = node;
        back_ = node;
      } else {
        auto* prev_node = FindNode(index - 1);
        node->next = prev_node->next;
        prev_node->next = node;
      }
    }
      size_ += 1;
      return true;
    }


  bool LinkedList::Set(int index, int new_value) {
    auto* node = FindNode(index);
    if (node != nullptr) {
      node->value = new_value;
      return true;
    }
    else {
      return false;
    }
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index < 0 || index >= size_) {
      return std::nullopt;
    }
    if (index == 0) {
      auto* remove_node = front_;
      const int remove_value = remove_node->value;

      front_ = front_->next;
      delete remove_node;
      size_ -= 1;
      return remove_value;
    }
    auto* prev_node = FindNode(index - 1);
    auto* removed_node = prev_node->next;
    const int removed_value = removed_node->value;
    prev_node->next = removed_node->next;
    delete removed_node;
    size_ -= 1;

    return removed_value;
  }


  void LinkedList::Clear() {
   for (Node* curr = front_; curr != nullptr; /**/) {
     Node* node_to_remove = curr;
     curr = curr->next;
     delete node_to_remove;
   }
   front_ = nullptr;
   back_ = nullptr;
   size_ = 0;
  }

  std::optional<int> LinkedList::Get(int index) const {
    auto* node = FindNode(index);
    if (node == nullptr) {
      return std::nullopt;
    }
    return node->value;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    int count = 0;
    for (auto* curr_node = front_; curr_node != nullptr; curr_node = curr_node->next) {
      if (curr_node->value == value) {
        return count;
      }
      count += 1;
    }
  }

  bool LinkedList::Contains(int value) const {
    return IndexOf(value).has_value();
    return true;
  }

  bool LinkedList::IsEmpty() const {
    return front_ == nullptr;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (front_ != nullptr) {
          return front_->value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
    if (back_ != nullptr) {
      return back_->value;
    }
    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
    if (index < 0 || index >= size_) {
      return nullptr;
    }
    int count = 0;

    for (auto* node = front_; node != nullptr; node = node->next) {
      if (count == index) {
        return node;
      }
      count += 1;
    }

return nullptr;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment