#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/*
 * Поиск объекта по цвету
 *
 */

using namespace cv;

int main()
{
    Mat frame, filter;
    // Объект для работы с камерой и видеофайлами,
    // в случае передачи 0 в конструктор
    // открывает камеру по умолчанию
    VideoCapture cap(0);

    namedWindow("Filter");
    int minH = 0, maxH = 255, minS = 0, maxS = 255, minV = 0, maxV = 255;
    int er = 0, dil = 0;
    createTrackbar("Min Hue", "Filter", &minH, 255);
    createTrackbar("Max Hue", "Filter", &maxH, 255);
    createTrackbar("Min Sat", "Filter", &minS, 255);
    createTrackbar("Max Sat", "Filter", &maxS, 255);
    createTrackbar("Min Val", "Filter", &minV, 255);
    createTrackbar("Max Val", "Filter", &maxV, 255);
    createTrackbar("Erode", "Filter", &er, 12);
    createTrackbar("Dilate", "Filter", &dil, 12);

    for(;;)
    {
        // Получение нового кадра с камеры
        cap >> frame;

        cvtColor(frame, filter, COLOR_BGR2HSV);
        inRange(filter,                    // Исходное изображение
                Scalar(minH, minS, minV),  // Вектор минимальных значений
                Scalar(maxH, maxS, maxV),  // Вектор максимальных значений
                filter);                   // Результат

        erode(filter, filter, Mat(), Point(-1, -1), er);
        dilate(filter, filter, Mat(), Point(-1, -1), dil);

        imshow("Frame", frame);
        imshow("Filter", filter);

        if(waitKey(1) == 27) break;
    }

    return 0;
}
