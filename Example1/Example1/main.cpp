#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/*
 * Пример использования операции свёртки с помощью функции
 * Filter2D
 *
 */

// Принимаем 2 ссылки на изображения, т.к. исходное изображение мы не будем
// менять, то принимаем его по константной ссылке
void sharpen(const cv::Mat &input, cv::Mat &output)
{
    // Принимаем только 8-и битные изображения
    CV_Assert(input.depth() == CV_8U);
    // Создаём новое изображение такого же размера и типа, как исходное
    output.create(input.size(), input.type());
    // Количество каналов, для цветного изображения их 3: 1. Синий,
    // 2. Зелёный и 3. Красный
    const int nChannels = input.channels();
    // Цикл по всем строчкам изображения, кроме первой и последней
    for(int y = 1; y < input.rows - 1; ++y)
    {
        // Получаем указатели на начала текущей, предыдущей и следующей строчек
        // (Указывает на один субпиксель)
        const uchar *previous = input.ptr<uchar>(y - 1);
        const uchar *current  = input.ptr<uchar>(y    );
        const uchar *next     = input.ptr<uchar>(y + 1);
        // Получаем указатель на текущую строчку в изображении-результате
        uchar* res = output.ptr<uchar>(y);
        // Цикл по всем субпикселям в строчке, кроме первого и последнего
        // пикселя
        for(size_t i = nChannels; i < (input.step - 1); ++i)
        {
            // cv::saturate_cast<uchar> ограничивает значение результата в
            // диапазон соответствующий типу <uchar> (от 0 до 255)
            // uchar - unsigned char
            *res++ = cv::saturate_cast<uchar>(5 * current[i]
                                             -current[i - nChannels] -
                    current[i + nChannels] - previous[i] - next[i]);
        }
    }
    // Устанавливаем граничные значения равными 0
    output.row(0).setTo(cv::Scalar(0));
    output.row(output.rows - 1).setTo(cv::Scalar(0));
    output.col(0).setTo(cv::Scalar(0));
    output.col(output.cols - 1).setTo(cv::Scalar(0));
}

int main()
{
    cv::Mat input;
    cv::Mat output;
    cv::Mat output2;
    // Создаём матрицу ядра фильтра
    // Так как в фильтре присутствуют отрицательные числа,
    // создаём матрицу из 8-и битных переменных со знаком
    cv::Mat kernel = (cv::Mat_<int8_t>(3, 3) <<  0, -1,  0,
                                                -1,  5, -1,
                                                 0, -1,  0);
    // Читаем изображение из файла
    input = cv::imread("../../img/fruits.jpg");
    sharpen(input, output);
    // Функция cv::Mat::depth() const возвращает разрядность элементов
    // CV_8U  - 8-и битные беззнаковые целые числа
    // CV_8S  - 8-и битные знаковые целые числа
    // CV_16U - 16-и битные беззнаковые целые числа
    // CV_16S - 16-и битные знаковые целые числа
    // CV_32S - 32-и битные знаковые целые числа
    // CV_32F - 32-и битные числа с плавающей точкой
    // CV_64F - 64-и битные числа с плавающей точкой
    // Применяем функцию фильтрации с нашим фильтром
    cv::filter2D(input,            // Исходное изображение
                 output2,          // Результат
                 input.depth(),    // Разрядность пикселей
                 kernel            // Ядро фильтра
                 );
    // Отображение изображений в окне
    // Если окна ещё нет, то оно создаётся автоматически
    cv::imshow("Original", input);
    cv::imshow("Sharpened", output);
    cv::imshow("filter2D", output2);
    // Ожидание нажатия на клавишу на клавиатуре
    cv::waitKey();

    return 0;
}
