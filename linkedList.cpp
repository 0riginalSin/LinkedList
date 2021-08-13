/******************************************************************************
 * LinkedList version 1.0
 * @files linkedList.hpp linkedList.shpp
 * @author 0riginalSin
 * @brief This file contains the implimentation of LinkedList class methods.
 *
 * @attention Do not complile or #include this file. It's already include in
 * linkedList.h file cause of specific of template using. Just place this file
 * in directory with linkedList.h and include linkedList.h in your project.
 *
 * Standart linked list implimentation with class. You could use pointers to
 * have access to your data even after another data deleted pointer would stay
 * constant.
 ******************************************************************************
 */

namespace DataStructs {
	template <typename DataType>
	inline bool LinkedList<DataType>::StandartCompareFunction(const DataType& first, const DataType& second) {
		return first == second ? true : false;
	}
	template <typename DataType>
	LinkedList<DataType>::LinkedList() : lastMemberPointer_(nullptr), size_(0) {}
	template <typename DataType>
	LinkedList<DataType>::LinkedList(const uint8_t quantityOfMembers, const DataType* firstData, ...)
		: lastMemberPointer_(nullptr), size_(0) {
		DataType** parameterPointer = &firstData; //pointer to the parameter of function
		for (uint8_t i = 0; i < quantityOfMembers; i++) {
			this->Add(**parameterPointer);
			parameterPointer++; //go to next parameter of data to add
			size_++;
		}
	}
	template <typename DataType>
	LinkedList<DataType>::LinkedList(const LinkedList& copyInstance) : lastMemberPointer_(nullptr), size_(0) {
		size_t i = copyInstance.size_ - 1;
		if (i == SIZE_MAX) //same as: if( copyInstance.size_ == 0 )
			return;
		for (;; i--) {
			this->Add(*copyInstance[i]);
			if (!i) break;
		}
	}
	template<typename DataType>
	LinkedList<DataType>::~LinkedList() {
		Member* currentMember = lastMemberPointer_;
		Member* tempMember;
		while (currentMember != nullptr) {
			tempMember = currentMember;
			currentMember = currentMember->memberPointer_;
			delete tempMember;
		}
	}
	template <typename DataType>
	inline bool LinkedList<DataType>::IsEmpty() const {
		return lastMemberPointer_ == nullptr ? true : false;
	}
	template <typename DataType>
	void LinkedList<DataType>::Add(const DataType& data) {
		lastMemberPointer_ = new Member(Member{ data, lastMemberPointer_ });
		size_++;
	}
	template <typename DataType>
	void LinkedList<DataType>::Add(const uint8_t quantityOfMembers, const DataType* firstData, ...) {
		DataType** parameterPointer = &firstData;
		for (uint8_t i = 0; i < quantityOfMembers; i++) {
			this->Add(**parameterPointer);
			parameterPointer++;
			size_++;
		}
	}
	template <typename DataType>
	bool LinkedList<DataType>::Delete(size_t ordinalNum) {
		Member* tempMember = lastMemberPointer_;
		Member* memberToDelete;
		if (!ordinalNum) {
			tempMember = lastMemberPointer_->memberPointer_;
			delete lastMemberPointer_;
			lastMemberPointer_ = tempMember;
			size_--;
			return true;
		}
		while (tempMember->memberPointer_ != nullptr) { //while not end of lists
			if (!(ordinalNum - 1)) { //if next member is that we are looking for
				memberToDelete = tempMember->memberPointer_;
				tempMember->memberPointer_ = memberToDelete->memberPointer_;
				delete memberToDelete;
				return true;
				size_--;
			}
			ordinalNum--;
			tempMember = tempMember->memberPointer_;
		}
		return false;
	}
	template <typename DataType>
	void LinkedList<DataType>::Clear() {
		Member* currentMember = lastMemberPointer_;
		Member* tempMember;
		while (currentMember != nullptr) {
			tempMember = currentMember->memberPointer_; //go to another Member
			delete currentMember;
			currentMember = tempMember;
		}
		lastMemberPointer_ = nullptr;
		size_ = 0;
	}
	template <typename DataType>
	DataType* LinkedList<DataType>::Find(const DataType& dataToFind,
		std::function<bool(const DataType&, const DataType&)> compareFunc) const {
		Member* tempMember = lastMemberPointer_; //pointer to the Member, with which data we'r currently compare

		while (tempMember != nullptr) {
			//compare and send the data
			if (compareFunc(tempMember->data_, dataToFind))
				return &(tempMember->data_);
			tempMember = tempMember->memberPointer_; //go to another Member
		}
		//if nothing found
		return nullptr;
	}
	template <typename DataType>
	DataType* LinkedList<DataType>::Find(const DataType& dataToFind, size_t& ordinalNum,
		std::function<bool(const DataType&, const DataType&)> compareFunc) const {
		Member* tempMember = lastMemberPointer_; //pointer to the Member, with which data we'r currently compare
		ordinalNum = 0;

		while (tempMember != nullptr) {
			//compare and send the data
			if (compareFunc(tempMember->data_, dataToFind))
				return &(tempMember->data_);
			tempMember = tempMember->memberPointer_; //go to another Member
			ordinalNum++;
		}
		//if nothing found
		return nullptr;
	}
	template <typename DataType>
	DataType* LinkedList<DataType>::operator[](size_t ordinalNum) const {
		Member* tempMember = lastMemberPointer_; //pointer to the Member we work with
		while (tempMember != nullptr) {
			if (!ordinalNum)
				return &(tempMember->data_);
			--ordinalNum;
			tempMember = tempMember->memberPointer_;
		}
		return nullptr;
	}
	template <typename DataType>
	bool LinkedList<DataType>::operator==(const LinkedList& compare) const {
		Member* tempMemberThis = this->lastMemberPointer_; //pointer to the Member of this instanse
		Member* tempMemberCompare = compare.lastMemberPointer_; //pointer to the Member of compare instanse
		while (tempMemberThis != nullptr && tempMemberCompare != nullptr) { //while not end of lists
			if (!(tempMemberThis->data_ == tempMemberCompare->data_))
				return false;
			tempMemberThis = tempMemberThis->memberPointer_;
			tempMemberCompare = tempMemberCompare->memberPointer_;
		}
		if (tempMemberThis == tempMemberCompare) //if size of lists are equal
			return true;
		else
			return false;
	}
	template <typename DataType>
	bool LinkedList<DataType>::Compare(const LinkedList& compare,
	 std::function<bool(const DataType&, const DataType&)> compareFunc) const {
		Member* tempMemberThis = this->lastMemberPointer_; //pointer to the Member of this instanse
		Member* tempMemberCompare = compare.lastMemberPointer_; //pointer to the Member of compare instanse
		while (tempMemberThis != nullptr && tempMemberCompare != nullptr) {
			if (!compareFunc(tempMemberThis->data_, tempMemberCompare->data_))
				return false;
			tempMemberThis = tempMemberThis->memberPointer_;
			tempMemberCompare = tempMemberCompare->memberPointer_;
		}
		if (tempMemberThis == tempMemberCompare) //if size of lists are equal
			return true;
		else
			return false;
	}
	template <typename DataType>
	inline size_t LinkedList<DataType>::Size() const {
		return size_;
	}
}

