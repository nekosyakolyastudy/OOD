#include "stdafx.h"

#include "../MultiGumballMachine/MultiGumBallMachineWithState.h"

using namespace with_state;

template <typename GumballMachineType>
void AssertState(const GumballMachineType& machine, const std::string& state, size_t gumballs, size_t coins)
{
	boost::format outputFormat = boost::format(R"(Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
Number of coins: %4%
)")
		% gumballs % (gumballs == 1 ? "" : "s")
		% state
		% coins;

	BOOST_CHECK_EQUAL(machine.ToString(), outputFormat.str());
};

BOOST_AUTO_TEST_SUITE(MultiGumBallMachine)

	BOOST_AUTO_TEST_SUITE(receive_gum_balls_at_amount_of_0_and_does_not_change_state_when)
		boost::test_tools::output_test_stream output;
		CMultiGumballMachine machine(0, output);

		BOOST_AUTO_TEST_CASE(insert_quarter)
		{
			machine.InsertCoin();
			BOOST_CHECK(output.is_equal("You can't insert a quarter, the machine is sold out\n"));
			AssertState(machine, "sold out", 0, 0);
		}

		BOOST_AUTO_TEST_CASE(eject_quarter)
		{
			machine.EjectCoin();
			BOOST_CHECK(output.is_equal("You can't eject, you haven't inserted a quarter yet\n"));
			AssertState(machine, "sold out", 0, 0);
		}

		BOOST_AUTO_TEST_CASE(turn_crank)
		{
			machine.TurnCrank();
			BOOST_CHECK(output.is_equal("You turned but there's no gumballs\nNo gumball dispensed\n"));
			AssertState(machine, "sold out", 0, 0);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(receive_gum_balls_at_amount_greater_than_0)
		boost::test_tools::output_test_stream output;
		struct CMultiGumBallMachine_
		{
			CMultiGumBallMachine_()
				: machine(13, output)
			{
			}
			CMultiGumballMachine machine;
		};

		BOOST_FIXTURE_TEST_SUITE(is_at_NoQuarter_state, CMultiGumBallMachine_)

			BOOST_AUTO_TEST_CASE(changes_state_when_insertion_quarter)
			{
				machine.InsertCoin();
				BOOST_CHECK(output.is_equal("You inserted a quarter\n"));
				AssertState(machine, "waiting for turn of crank", 13, 1);
			}

			BOOST_AUTO_TEST_CASE(do_not_change_state_when_eject_quarter)
			{
				machine.EjectCoin();
				BOOST_CHECK(output.is_equal("You haven't inserted a quarter\n"));
				AssertState(machine, "waiting for quarter", 13, 0);
			}

			BOOST_AUTO_TEST_CASE(do_not_change_state_when_turn_crank)
			{
				machine.TurnCrank();
				BOOST_CHECK(output.is_equal("You turned but there's no quarter\nYou need to pay first\n"));
				AssertState(machine, "waiting for quarter", 13, 0);
			}
		BOOST_AUTO_TEST_SUITE_END()

		struct CMultiGumBallMachineHasQuarter_
		{
			CMultiGumBallMachineHasQuarter_()
				: machine(13, output)
			{
				machine.InsertCoin();
			}
			CMultiGumballMachine machine;
		};

		BOOST_FIXTURE_TEST_SUITE(is_at_HasQuarter_state, CMultiGumBallMachineHasQuarter_)

			BOOST_AUTO_TEST_CASE(do_not_change_state_when_insertion_quarter)
			{
				machine.InsertCoin();
				BOOST_CHECK(output.is_equal("You inserted a quarter\nYou can't insert another quarter\n"));
				AssertState(machine, "waiting for turn of crank", 13, 0);
			}

			BOOST_AUTO_TEST_CASE(changes_state_when_eject_quarter)
			{
				machine.EjectCoin();
				BOOST_CHECK(output.is_equal("You inserted a quarter\nQuarter returned\n"));
				AssertState(machine, "waiting for quarter", 13, 0);
			}

			BOOST_AUTO_TEST_CASE(changes_state_when_turn_crank)
			{
				machine.TurnCrank();
				BOOST_CHECK(output.is_equal("You inserted a quarter\nYou turned...\nA gumball comes rolling out the slot...\n"));
				AssertState(machine, "waiting for quarter", 12, 0);
			}

			BOOST_AUTO_TEST_CASE(changes_state_when_get_last_gum_ball)
			{
				CMultiGumballMachine gumballMachine(1, output);
				gumballMachine.InsertCoin();
				gumballMachine.TurnCrank();
				AssertState(gumballMachine, "sold out", 0, 0);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
