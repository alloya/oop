#include "stdafx.h"
#include "../MyArray/MyArray.h"

using namespace std;

struct StackOfInt
{
	CMyStack<int> stack;
};


BOOST_FIXTURE_TEST_SUITE(MyArray, StackOfInt)
	BOOST_AUTO_TEST_CASE(is_empty_by_default)
	{
		BOOST_CHECK(stack.IsEmpty());
	}

	BOOST_AUTO_TEST_CASE(can_push_items)
	{
		stack.Push(1);
		BOOST_CHECK_EQUAL(stack.GetSize(), 1);
	}

	BOOST_AUTO_TEST_CASE(can_pop_items)
	{
		stack.Push(1);
		stack.Pop();
		BOOST_CHECK(stack.IsEmpty());
	}

	BOOST_AUTO_TEST_CASE(cant_pop_items_when_stack_is_empty)
	{
		BOOST_CHECK_THROW(stack.Pop(), std::underflow_error);
	}

	BOOST_AUTO_TEST_CASE(can_get_stack_top)
	{
		stack.Push(15);
		stack.Push(35);
		BOOST_CHECK_EQUAL(stack.GetTop(), 35);
		BOOST_CHECK_EQUAL(stack.GetSize(), 2);
	}

	BOOST_AUTO_TEST_CASE(cant_get_stack_top_when_stack_is_empty)
	{
		BOOST_CHECK_THROW(stack.GetTop(), std::underflow_error);
	}

	BOOST_AUTO_TEST_CASE(can_clear_stack)
	{
		stack.Push(1);
		stack.Push(2);
		stack.Push(3);
		stack.Clear();
		BOOST_CHECK(stack.IsEmpty());
	}


	BOOST_AUTO_TEST_CASE(can_be_copied)
	{
		stack.Push(1);
		stack.Push(2);
		CMyStack<int> stack2(stack);
		stack2.Pop();
		BOOST_CHECK(stack2.GetTop() == 1);
		BOOST_CHECK(stack.GetTop() == 2);
	}


	BOOST_AUTO_TEST_CASE(can_be_moved)
	{
		{
			stack.Push(35);
			CMyStack<int> stack1(std::move(stack));
			BOOST_CHECK(stack1.GetTop() == 35);
			BOOST_CHECK(stack.IsEmpty());
		}

		{
			stack.Push(24);
			CMyStack<int> stack1;
			stack1 = std::move(stack);
			BOOST_CHECK_EQUAL(stack1.GetTop(), 24);
			BOOST_CHECK(stack.IsEmpty());
		}
	}

	BOOST_AUTO_TEST_CASE(can_be_assigned)
	{
		{
			stack.Push(35);
			CMyStack<int> stack1;
			stack1 = stack;
			BOOST_CHECK_EQUAL(stack.GetTop(), 35);
			BOOST_CHECK_EQUAL(stack1.GetTop(), 35);
		}
	}

	BOOST_AUTO_TEST_CASE(can_be_assigned_to_itself)
	{
		{
			stack.Push(35);
			stack = stack;
			BOOST_CHECK_EQUAL(stack.GetSize(), 1);
			BOOST_CHECK_EQUAL(stack.GetTop(), 35);
		}
	}
BOOST_AUTO_TEST_SUITE_END()
