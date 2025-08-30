#include <iostream>
#include <thread>

using namespace std;

void
d()
{
  chrono::milliseconds dur(500);

  float progress = 0.0;
  do
  {
    int barWidth = 70;

    cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i)
    {
      if (i < pos)
        cout << "=";
      else if (i == pos)
        cout << ">";
      else
        cout << " ";
    }
    cout << "] " << int(progress * 100.0) << " %\r";
    cout.flush();
    this_thread::sleep_for(dur);
    progress += 0.1; // for demonstration only
  } while (progress < 1.0);
  cout << endl;
}
