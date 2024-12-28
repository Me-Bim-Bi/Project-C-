# 1. Dynamic_cast and Clone:
- Khi nào sử dụng dynamic_cast hoặc clone trong dự án của bạn?
  - Nên dùng dynamic_cast nếu:
  - Bạn cần phân biệt giữa các lớp con (ví dụ: Clothing và Cosmetic) để xử lý logic riêng cho từng lớp.
  - Bạn không muốn sao chép đối tượng.
  -  Bạn đang xử lý đối tượng trực tiếp (không thêm vào container).
- Nên dùng clone nếu:
  - Bạn cần thêm các đối tượng vào container (như std::vector<Product*>) mà không muốn sửa đổi trực tiếp đối tượng ban đầu.
  - Bạn muốn bảo toàn nguyên tắc "đóng gói" của lập trình hướng đối tượng bằng cách không để các lớp bên ngoài phụ thuộc vào việc kiểm tra kiểu.
  - Đối tượng có thể thay đổi hoặc cần lưu trữ bản sao độc lập.

  # 2. Dòng return khi không mở/đóng được file:
  ```
  if (!file.is_open()) {
        std::cerr << "Could not open the file for writing: " << filename << std::endl;
        return;`
  ```
  - Đảm bảo không thực thi mã tiếp theo
    - Nếu file không thể mở được (ví dụ: do quyền truy cập, file không tồn tại, hoặc lỗi đường dẫn), thì hàm không thể tiếp tục ghi dữ liệu vào file.
    - Nếu không có dòng return, hàm sẽ cố gắng ghi thông tin từ vector products vào file, dẫn đến các lỗi nghiêm trọng như:
      - Lỗi runtime: Khi gọi các phương thức ghi dữ liệu (file << ...) trên một đối tượng ofstream không hợp lệ, kết quả là chương trình sẽ gặp lỗi hoặc ghi dữ liệu rỗng vào file.
      - Mất dữ liệu: Có thể gây ra dữ liệu không mong muốn trong file đầu ra, làm hỏng file hoặc ghi sai định dạng.
- Thông báo lỗi và dừng hoạt động
    - Dòng std::cerr << ... in thông báo lỗi cho người dùng, cho biết lý do thất bại.
    - Sau khi thông báo lỗi, return đảm bảo hàm dừng lại ngay tại chỗ, tránh tiếp tục thực hiện các logic không có ý nghĩa khi file không thể mở.
- Bảo vệ tài nguyên
    - Trong trường hợp này, file là một tài nguyên (file handle). Nếu file không mở được, việc tiếp tục sử dụng sẽ không chỉ gây lỗi mà còn có thể dẫn đến rò rỉ tài nguyên (nếu có các xử lý khác phụ thuộc vào file này).
 
# 3. Vì sao cần dùng const ở đây và đặt string type ngoài vòng lặp thì có được không:
- const: Đảm bảo rằng các giá trị không bị thay đổi ngoài ý muốn, giúp hàm an toàn và dễ bảo trì hơn.
- Khai báo std::string type: Nên khai báo bên trong vòng lặp, vì:
    - Giới hạn phạm vi sử dụng.
    - Cải thiện độ rõ ràng và tính đúng đắn của mã.
    - Không làm ảnh hưởng đáng kể đến hiệu suất.
