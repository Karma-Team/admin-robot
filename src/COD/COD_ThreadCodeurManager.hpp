#include "THD_Queue.hpp"
#include "THD_ThreadSafeObject.hpp"

#define PIN_GPIO_SA_DROITE 30 ///< gpio 27 ou en partan du haut gpio 7
#define PIN_GPIO_SB_DROITE 21 ///< gpio 29 ou en partan du haut gpio 6

#define PIN_GPIO_SA_GAUCHE 22 ///< gpio 31 ou en partan du haut gpio 5
#define PIN_GPIO_SB_GAUCHE 23 ///< gpio 33 ou en partan du haut gpio 4

namespace COD
{
	class CThreadCodeurManager
	{
		public:

			CThreadCodeurManager();

			virtual ~CThreadCodeurManager();

			void initialisation();

		    void reset();

			int getTicksDroit();
			int getTicksGauche();


		private:

			 static void compterTicDroit();
			 static void compterTicGauche();

	};
}

