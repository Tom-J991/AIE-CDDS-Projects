#include "pch.h"
#include "CppUnitTest.h"

#include "doublylinkedlist.h"
#include "listnode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		TEST_METHOD(Insert)
		{
			if (!m_doublyLinkedList.Empty())
				m_doublyLinkedList.Clear(); // Remove everything from list if not empty.

			// Initialize list at head and tail.
			m_doublyLinkedList.PushFront(10);
			m_doublyLinkedList.PushBack(5);

			// Test Insert Method
			int value = 8;
			m_doublyLinkedList.Insert(m_doublyLinkedList.First(), value); // Inserts value before head, should be new head.

			Assert::AreEqual(m_doublyLinkedList.First()->GetData(), value); // Should be equal if value was inserted at head.
		}

		TEST_METHOD(Remove)
		{
			if (!m_doublyLinkedList.Empty())
				m_doublyLinkedList.Clear(); // Remove everything from list if not empty.

			// Initialize list at head and tail.
			m_doublyLinkedList.PushFront(10);
			m_doublyLinkedList.PushBack(5);

			// Test Remove Method
			int value = 6;
			m_doublyLinkedList.PushFront(value); // Insert value to remove at head.
			m_doublyLinkedList.Remove(value); // Remove value.

			Assert::AreNotEqual(m_doublyLinkedList.First()->GetData(), value); // Shouldn't be equal if value was removed from head.
		}

		TEST_METHOD(Sort)
		{
			if (!m_doublyLinkedList.Empty())
				m_doublyLinkedList.Clear(); // Remove everything from list if not empty.

			// Insert test values.
			m_doublyLinkedList.PushBack(7);
			m_doublyLinkedList.PushBack(11);
			m_doublyLinkedList.PushBack(1);
			m_doublyLinkedList.PushBack(18);
			m_doublyLinkedList.PushBack(4);
			m_doublyLinkedList.PushBack(6);
			m_doublyLinkedList.PushBack(2);
			m_doublyLinkedList.PushBack(12);

			// Test Sorting Method

			m_doublyLinkedList.Sort();

			Assert::AreEqual(m_doublyLinkedList.First()->GetData(), 1); // Test if head is sorted correctly.
			Assert::AreEqual(m_doublyLinkedList.Last()->GetData(), 18); // Test if tail is sorted correctly.
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			// Clean up
			m_doublyLinkedList.Clear();
		}

	private:
		DoublyLinkedList m_doublyLinkedList;

	};

}
