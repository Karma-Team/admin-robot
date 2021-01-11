
#define SPI_CHANNEL 0
#define SPI_CLOCK_SPEED 1000000

namespace COD
{
	class CSPICodeurManager
	{
		public:

			CSPICodeurManager();

			virtual ~CSPICodeurManager();

			void initialisation();
			void closeS();

		    void readAndReset();
		    void reset();

			int getRightTicks();
			int getLeftTicks();


		private:
			int m_leftTicks;
			int m_rightTicks;

	};
}

