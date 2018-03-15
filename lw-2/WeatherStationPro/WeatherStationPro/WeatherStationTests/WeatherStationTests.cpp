﻿#include "stdafx.h"
class CTestObserver : public IObserver<SWeatherInfo>
{
public:
	CTestObserver(const CWeatherData& in, const CWeatherData& out, std::stringstream& strm) :
		m_in(in),
		m_out(out),
		m_strm(strm)
	{
	}

private:
	void Update(SWeatherInfo const& data, const IObservable<SWeatherInfo>& observable) override
	{
		if (&observable == &m_in)
		{
			m_strm << "in station";
		}
		else if (&observable == &m_out)
		{
			m_strm << "out station";
		}
	}

	const CWeatherData & m_in;
	const CWeatherData & m_out;
	std::stringstream& m_strm;
};


BOOST_AUTO_TEST_SUITE(Weather_station)
	BOOST_AUTO_TEST_CASE(observer_identifies_changed_subject)
	{
		CWeatherData in;
		CWeatherData out;
		std::stringstream strm;

		CTestObserver testObserver(in, out, strm);
		in.RegisterObserver(testObserver);
		out.RegisterObserver(testObserver);
		
		{
			in.SetMeasurements(4, 0.8, 761, 10, 90);
			BOOST_CHECK_EQUAL(strm.str(), "in station");
		}
		strm.str("");
		{
			out.SetMeasurements(4, 0.8, 761, 10, 90);
			BOOST_CHECK_EQUAL(strm.str(), "out station");
		}

		{
			CWeatherData other;
			other.RegisterObserver(testObserver);
			strm.str("");

			other.SetMeasurements(4, 0.8, 761, 10, 90);
			BOOST_CHECK_EQUAL(strm.str(), "");
		}
	}
BOOST_AUTO_TEST_SUITE_END()


