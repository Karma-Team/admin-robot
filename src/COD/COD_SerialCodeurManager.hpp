
#ifndef _CSERIALCODEURMANAGER_
#define _CSERIALCODEURMANAGER_

#define CMD_RESET -3

namespace COD
{
	class CSerialCodeurManager
	{
		public:

			CSerialCodeurManager(char* m_codeurSerieTty);

			virtual ~CSerialCodeurManager();

			void initialisation();
			void closeS();

		    void readAndReset();
		    void reset();

			int getRightTicks();
			int getLeftTicks();


		private:
			char m_codeurSerieTty[14];
			int m_leftTicks;
			int m_rightTicks;

	};
}

#endif

