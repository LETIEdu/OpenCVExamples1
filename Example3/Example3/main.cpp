#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/*
 * Расчёт производных изображения
 *
 */


int main()
{
  cv::Mat src, srcGray;
  cv::Mat grad;
  src = cv::imread("../../img/lena.jpg");
  cv::GaussianBlur(src, src, cv::Size(3, 3), 0, 0);
  // Преобразуем цветное изображение в чёрнобелое
  // Код преобразования из исходного (INIT) цветового пространства
  // в желаемое (DESIR) строится следующим образом:
  // cv::COLOR_INIT2DESIR
  // Примеры:
  // cv::COLOR_BGR2GRAY из цветного (BGR) в чёрнобелое (GRAY)
  // cv::COLOR_BGR2HSV из цветного (BGR) в цветное (HSV)
  cv::cvtColor(src,                // Исходное изображение
               srcGray,            // Результат
               cv::COLOR_BGR2GRAY  // Код преобразования
               );
  cv::Mat gradX, gradY;
  cv::Mat absGradX, absGradY;
  // Применение оператора Шарра
  // Один из порядков производной должен быть равен 1,
  // а второй 0. Другие комбинации не поддерживаются
  cv::Scharr(srcGray, // Исходное изображение
             gradX,   // Результат
             CV_16S,  // Разрядность результата
             1,       // Порядок производной по оси x
             0);       // Порядок производной по оси y
  // Функция cv::convertScaleAbs производит масштабирование,
  // расчёт модуля каждого пикселя и приведение их к типу uchar
  cv::convertScaleAbs(gradX,
                      absGradX);
  cv::Scharr(srcGray, gradY, CV_16S, 0, 1);
  cv::convertScaleAbs(gradY, absGradY);
  // Взвешенная сумма изображений, каждый пиксель рассчитывается как:
  // dst = src1*alpha + src2*beta + gamma
  cv::addWeighted(absGradX,  // Исходное изображение (src1)
                  0.5,       // alpha
                  absGradY,  // Исходное изображение (src2)
                  0.5,       // beta
                  0,         // gamma
                  grad);     // Результат
  cv::imshow("X Derivative", absGradX);
  cv::imshow("Y Derivative", absGradY);
  cv::imshow("Full Derivative", grad);
  cv::waitKey();

  return 0;
}
