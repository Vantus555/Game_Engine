#pragma once

namespace Vantus {

	class TimeStep {
	public:
		TimeStep(float seconds)
			: m_Seconds(seconds), m_MilliSeconds(seconds * 1000){ }

		operator float() const { return m_Seconds; }

		float GetSeconds() const { return m_Seconds; }
		float GetMilliSeconds() const { return m_MilliSeconds; }
	private:
		float m_Seconds;
		float m_MilliSeconds;
	};

}