
#define CMD_RESET -3

namespace COD
{
	class CSerialCodeurManager
	{
		public:

			CSerialCodeurManager(char* p_servoSerieTty);

			virtual ~CSerialCodeurManager();

			void initialisation();
			void closeS();

		    void readAndReset();
		    void reset();

			int getRightTicks();
			int getLeftTicks();


		private:
			char m_servoSerieTty[14];
			int m_leftTicks;
			int m_rightTicks;

	};
}

