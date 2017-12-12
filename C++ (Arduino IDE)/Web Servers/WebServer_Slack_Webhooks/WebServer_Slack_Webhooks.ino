#include <ESP8266WiFi.h>

/*
 CIRCUIT CONFIGURATION
 */
const int ledPin = D3;
const int buttonPin = D6;

/*
 WIFI CONFIGURATION
 */
char SSID[] = "Dougras";
char pwd[] = "eusouodougrasvocenaoehodougras";
WiFiServer server(80);

/*
 SLACK CONFIGURATION
 */
const String slack_hook_url = "https://hooks.slack.com/services/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";
const String slack_icon_url = "https://pbs.twimg.com/profile_images/1462227900/cda288d94c3e99d0ccc4e8d1c61d7073_normal.jpg";
const String slack_message = "#GoEMakers - mensagem enviada pelo ESP8266 by Arduino Firmware";
const String slack_username = "esp_milgrau";

void setup()
{ 
  Serial.begin(115200);

  WiFi.begin(SSID, pwd);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
   // Start the server
  server.begin();
}

void consultaServidor(){
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  String buf = "";
  
  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
  buf += "<html lang=\"en\"><head><meta charset=\"UTF-8\" name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  buf += "<title>EMakers - Curso ESP8266</title>";
  buf += "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:30%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:20%;} </style>";
  buf += "</head>";
  buf += "<script> function mudaCor(el){el.style.backgroundColor = '#000000';}</script>";
  buf += "<h3>CURSO ESP8266 - Botão de envio de mensagens</h3>";
  buf += "<p>Mensagem_1: <a href=\"?function=mensagem1\"><button onclick=\"mudaCor(this)\">ENVIAR</button></a></p>";
  buf += " <input type=\"text\" name=\"fname\" id=\"text1\">";
  //buf += "<script> var input = document.getElementById(\"input_id\").value; if (input == \"oi\") {document.getElementById(\"input_id\").value = \"tchau\" }</script>";
  buf += "<p>Mensagem_2: <a href=\"?function=mensagem2\"><button onclick=\"mudaCor(this)\">ENVIAR</button></a></p>";
  //buf += "<img src=\"data:image/jpeg;base64,/9j/4AAQSkZJRgABAQIAdgB2AAD/2wBDAAEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQH/2wBDAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQH/wAARCAB4AIMDAREAAhEBAxEB/8QAHwAAAQUBAQEBAQEAAAAAAAAAAAECAwQFBgcICQoL/8QAtRAAAgEDAwIEAwUFBAQAAAF9AQIDAAQRBRIhMUEGE1FhByJxFDKBkaEII0KxwRVS0fAkM2JyggkKFhcYGRolJicoKSo0NTY3ODk6Q0RFRkdISUpTVFVWV1hZWmNkZWZnaGlqc3R1dnd4eXqDhIWGh4iJipKTlJWWl5iZmqKjpKWmp6ipqrKztLW2t7i5usLDxMXGx8jJytLT1NXW19jZ2uHi4+Tl5ufo6erx8vP09fb3+Pn6/8QAHwEAAwEBAQEBAQEBAQAAAAAAAAECAwQFBgcICQoL/8QAtREAAgECBAQDBAcFBAQAAQJ3AAECAxEEBSExBhJBUQdhcRMiMoEIFEKRobHBCSMzUvAVYnLRChYkNOEl8RcYGRomJygpKjU2Nzg5OkNERUZHSElKU1RVVldYWVpjZGVmZ2hpanN0dXZ3eHl6goOEhYaHiImKkpOUlZaXmJmaoqOkpaanqKmqsrO0tba3uLm6wsPExcbHyMnK0tPU1dbX2Nna4uPk5ebn6Onq8vP09fb3+Pn6/9oADAMBAAIRAxEAPwD+/igAoAKACgA6UAfCv7Tv/BRX9mb9lm8m8L+LPFF542+KQgE1t8IfhlZR+LfHmJFcwSa5bw3Nvo/g2zkYRt9r8X6voweF/OtYbtRtP6twJ4M8deIChisry2OAyaUuWWf5xOWByvRrm+qycJ4nMZpNrly/D4iMZrlqTp7n5D4ieOPh54Z06sM/zmFbNKcOb+xctdPFZim03BYlOpTw2A5vdcfr1ejUnGSlSpVNn+bHgL/gq5+0T8cv2hvg34C8NfC/4cfCD4Z+Mfir4J8Oa7Fr+p6p8RviXqHh3VdctbPUraK90yTw/wCD/DF/eWkjxiWG28RvYO+6Ked0Vz++Zv8ARq4a4V4I4oz3M8/zXO85yrh3N8wwscHSoZVlVPGYXB1K1GUqVRY3G4unTqRTtOthPaJe9TinY/lzJ/pk5lxj4jcG8KZBw5g8uyfP+K8jybFYrGVK2Ox8sJjsdSw9eVOpfB4ejOVOcmuTCV+RtctZtcz/AD9+JH7Xv7auteMfFsN3+1x8W9Ms7LxX4msbHT/B9h8PvBljZ2Njr2o2ljaxDSfBzXcq21pDDD51zdyzzbPNmdpGY1+35B4M+FdDK8tqrgfJ8TVrZdl9erVx9XM8fUqVq2DoVas39Zx86a56k5y5YwjFXUVFRSt/NXE/0ovGavnWb0KPFmJwWHw2bZphaFLB08Jho06OFzDE4elFPDYShKXLTpRjzSk5Nq7bbbPUP2df2jv2qJ7b9oe81H9qT42a/deHP2X/AIn+KPDDeJ9Y8OeILfw/4s0rXPAkekeJbGyvfDK202pabFe38MEd8t1YPDfXCXFpNmMx+Bx34X+HVGrwPSw3BeQ4SOZeIPD+V476lQxGElisuxWEziWJwk50cVGUadWVClKTpuFS9OPLNap/UeGf0hPFjG0vEerj+K8dj5ZF4W8UcR5d9bn7eNDNMtx2RUsLXjGtGrF8kMZXi1KM01KyW56/+yf/AMFFf21tV+OPwm+Gfjzxz8Ofip4Q8e/EHwv4M1q88S/DyDwp4z0vS9b1KKxudR0jV/A19puiXep2kT+bBDq3h9ra5dfLlkj3bx8n4lfR+8OMBwjxHxDkmGzjJMdkuS5hm+Ho4bNJ43L8RVwlCVaNHEYfM6eJxEKNS3LJ0MXCUE7xTtY+78Ivpc+IeecccJcJcR0MrzXC8R8QZZkdTFvBUsNjMPHH4mGH9vSq4GWCpOdPm5mquFrRls97n6C/Bz/grv8As7eNfFlz8PPjBZa3+zv4zi8Qan4d0668fTWd38NvEl3p+rXOlQNovxM0w/2HYzagbdZotO8WQ+G7iNpRbLNdSKGf8I4r+jnx5kOX0s4yanQ4uyueDw+Nqf2PCpHOMJTr4aGJl9YyWq5YitGlGdpVMuq426Tm6dNOy/qPgf6UPhpxfmGIybGY7/VnN8PjsVgXSzepBZdWq4fFVMKlTzOKp08O5zpydsxo4KF/dp1a11J/qrZ3tnqFvFd2NzBd208aTQz20sc8MsUqh45I5YmdJI5EZXjkRmR0IZGZSCfwGUZRcoyjKMoylGUZRcZRlF2lGUZJSjKLTUoySlFpppNWP6OjKM4xlCUZRlGMoyjJSjKMkpRlGUW4yjKLUoyi3GUWpRbTTLVIoKACgAoAKACgAoAKAIp54baGW4uJY4III5JppppEiiiiiQySSyySFUjjjRWd3dlREVmZgoJFQhKpKMIRlKcpKMYxTlKUpNKMYxSbcm2kkk220km2TOcacZTnKMYRi5SlJqMYxim5SlJtJRSTbbaSSbbSR/P9/wAFIP2/vjRD4gi+B37P51H4aeAtd8MaR4lvP2j9NutN1DUvib4b8RWS3Fqn7P2sabdalpEHh5Y5jZa58RxNNq9pqiTaVodjpdzbLql1/ZXgN4J8O5lhZ8V8Wyo5vjsFmFfALhCtTq0oZLjsHUcakeKcJXhRryxr5Y1sPlM4RwksPKNbETxak8PR/g76Tv0j8/4RxFHg3g6hXy95pllHM6fFcJwlTzXLcZC0K/DmNw86lD6jGblQr5hQqSxzxMJ0aKwEYxxOI/EHStG07RYriPT7cpJe3Et7qV5PNNe6nq9/Oxe41HWdVvJJtQ1fUbmQtLcX2oXNxcSyMWLjOB/aUYqMYQUYwhThGnTp04xp0qVOCtClSpQUYU6UI2jCnCMYRSSjFWP8zsdj8bmeIqYvMMTWxeIqznUnUrTlNuc25TkuZv3pNtyk25zetSU5an0t+yYCf2pP2c8DOPjZ8OSfp/wkllzXwvij/wAm348/7JHP/wD1X1T9B8FP+TxeFf8A2X/C/wD6tcOeQ+NOPGnjXPH/ABWni888cf8ACS6pzX1WTf8AInyj/sU5X/6r8MfD58v+F7P/APsf57+Ob4233nuH7OX/ACDf2nv+zRfi5/6f/h3Xx/Hv+9eHP/Z0OF//AFCz0/Q/Cv8A3Xxf/wCzH8b/APqx4ZKX7Jf/ACdV+zr/ANlr8Af+n63rTxP/AOTacdf9kfnf/qDM5vBT/k8vhZ/2X/Df/qypHinja1tr3xV42s722t7y0ufF/i2K5tLuGO5tbiJvEepho57eZXimRhwVkRhj0r6zK21lGVyTaccqy1pp2aay/Du6fR9nuuh8Nm850+IM6qU5yp1I59nbjUhJwnF/2vjPhlFpq/XWzWjuj9KdN/bS+KH7Eum/sg23hzTh41+Ak/7Ivw0v/G/wqhiiTxFpbR+K/iLBdeM/h5q87+bc65b6Va2ltfeFNXmk07XtP0uyt7CfTdQiiuG/mDNPBnJvFGv4n4ynX/sni/C+JnEGFyzN25ywWKpLLckq08tzfCw0lhZV61WVPHYeKxmCqVqlRrE0nKg/724b+khmnhVh/BjKc5pvNeFM48HuFMyzPDv2cMXhsZXzXiLC1cwwOIcYKliFh8Jh4zoVpPA4uNGNOqsLV5MXH+jzwZ400jxrpFnqumS4N1YaXfvaS7Uu7aLV9JsdaskurcOz2txJpupWVzJay4mgWdBIOQT/AAzi8JiMDia+ExMPZ1qFatRmtXFyoV6uHnKlOyVWi6tGrGnWh7lTkk46qSX+jeExeHx2Go4rDVFUo16VGtB6KSjXo0sRTjUhdulV9jWpTnSk+aHPG91KMpdfXMdIUAFABQAUAFABQB+I3/BVX40+NvH3w/8AGXwO+Avi7Rr7w54F1Wysv2zE8J6xef8ACyfB3hHXdG0/V/CfhibT4LWP7H4I8bC+eDx94o0vULifRrK3g8OapBYWmtajOv8AVf0deEcqwfEGVcScYYDFYfEZrRq1PDiWYYaCybNsywletRx+Io4iU5Keb5f7JSynA4inT9u5VcdhXWrYfDRf8bfSs8Qs8w/BeeZHwLisNjpZVUo0fEWnl9d1M5yDKsdQpVMDVxeEio1I5FipVOTNsdh5VY0J/V8DjfYYWvjJR/Jf4QfFHwhH4Ni+AHxptLq5+CM11Jc+ENb0WzS58U/ADxNdKsP/AAl3gG1Azd+FrrCL45+HilbDX7FZNQ02OHXoQ19/WPE/DGZQzP8A114MlQocWUaMKOZYDETdHK+Ncso6rKc5ktKOYUVf+xc8a9tga3LQxM54KX7n/PTg/jnK8VlE/D7xKeMzDgfGYurjMrzmhD63n/h3nmLf7ziDIFN8+KyvEza/1k4av9XzPD82JwcKWYU17fz74sfCfxP8H/E6eHvEL6dqlhqmnweIPBvjLw/cfb/CHj/wjfHOl+LfCOqrmO+0q9Qqs8DML7R77zdL1SGG7i/efQ8McT5dxXlzx2BVfDV8NXngc2ynHQ9hmuR5pR/3nLM0wz96jiaLu4TS9ji6PLicNKdKXu/I8a8FZvwNm8cszSWFxmGxmFp5nkOfZZU+s5HxNkmI1wed5JjFeOIweIi0qtJv6xgcRz4TFwhWgnP2D4O6pbfCL4S65+0boXh3w/4o+JXhj4yeE/A3hi/8U2U2saB8JoZ/CmoeLrX4gS6Gl3aWd34k1/V7MeG/CGo648uk6NcaVqs9vbT6xNaovyXFeHq8U8U4PgHG4/HZbw/mPCmaZzmFDLa0cJjeJ5wzOhldTI44x0qtWnl+BwtV5hmtDBqGJxdPE4aE6kMJCo391wJjKXBHBWZeKmXZVluc8V5Rx3kvDmUYnOMPUx+W8FQqZNic8pcTTy6NahQr5rmWOoLKsjxWYOeDwFXBYydKlUx1SjFfM/8AwUg8d6d4B/Yvvv2tdE0LSPhh8QPGPwx+O1zeaR4Uin0rw3qPi3w3rWmeE/BvxY8G6Ne3F+2gW/izxH4w8i5sbOafQZPFfhTUr/Qkit57m2j+XzDiHMODeH/FnK4ZxjM0w/A+R5XUyDNsdVpVs1y7F59leIpYXIMfjadKnHGYzJcVDA4nB161L67DBY7C0cb7SpShOf2eV8I5T4icV+AudVOHsvyTF+J3FGdUeK8hyqjXw+R5vgOFs9weIxvFWWZZVr1p5dl/EuBqZpgsfhcPXeXVMxyzH4jLnRp1qtKHlv8AwR1+PGo/tC/sofFzxr4i1WXWPGVj+xv8X/C/jW/uTEb288S+G/EXw80m/wBQvBCscf2nVlt7fWpXWNBIdTDgfNgeJw3xdW4y4M8IM0xuIliczo+JfC+X5nWqcrq1cdgcHnuGrVqvIor2mJUIYqTS976xzaXPqeL+AcN4c+JH0gsjy7CRwWS1/BfjbNckw9JT9hRyvM8fwxi8Ph6PPKUvZYN1amCgnKTj9VcW9D7D/ZL/AOTqv2df+y1+AP8A0/W9fqvif/ybTjr/ALI/O/8A1BmfhXgp/wAnl8LP+y/4b/8AVlSPG/Fn/I5+L/8Asc/Ff/qSanX1mWf8ifLf+xTl3/qvw58JnX/I9zv/ALH2d/8Aq3xh9A/tWDHhT9lEf9WX/Do/n4l+JR/rxXw3ho/+FLxM/wCzt56v/LDh5fkfpfjKv+EXwXX/AFYHhb8c24sPsmw+OfxM+BP/AAUuTQ/B73uveBPjnJ+zj4H8ceCpLphb6f4m1j4J/DPQ/DXxC0VZmaKyureRbPRvFdumyLVNHa2u3/0zTIJU/AM98Psp4t8B6fEE1TwvEHB8uOs0y/MVC8sVluH4vz/EY7JcW4rmqUKyU8RgJu7weOSlC1HE4mMv7L4R8Xs14Q+khieBK85Ynh7jDDeHOWrCOajDC5lifD/henhcxw/N7kMTTqNQxCVvruBc6E+ath8FKH9EvhvX7LxNpFpq1hIHiuYwWXKlopV+WWJ9pIDxyBkYA4DKccV/FL0bWqs2mmrNNaNNdGuq6PQ/0GTuk976prVNd0+qe6ezWq0N6gAoAKACgAoA8Y/aD+Nngn9nf4Q+Mfi78QtYm0Pwv4VtbFbrUbXSZvEF5Fe63qtj4f0dLPQLW5tLzXLiTV9Usguk2VxFdXyCSGF1c5H0nCPDOacYcQ5bw9k2GjiswzCrUVKjOvHCU5U8NQq4vEOpipwqU8NBYehU/f1IuFOTi5aHzXF/FGU8G8O5nxHneKeCy3LqMJ18RGhLFSpyr1qeGoOOFhOFTEP29am3RpyU5wU1Fpq5/JrfaX8a/wBlL4tR+OpvGlt4p8Y+M77XviTb/F7T1GseCfjvpXjvUJrzxDrhhuGktNc8K+JVuBpPiDwbqTvPoKRQ6LdpbXNjpt+f9NMqjwj4gcIPIVldTA4DLKeFyXGcOYi+EznhHMcqpRp4XDOUEquBzLL3SVfLc0oJQxcV9ZpyqU6uIon+MXGGZeIHhz4my4wjnNLG4zOJYnOsi4owko5lw5xvw3mtWUq9ZKX+zZplOaxqSo51k+I/eYPETlha0aNWlg8QdL8Qvh54Q+IvhLVfjp8CNL/snR9IWK5+MnwZhme81P4N393J5f8Awkvhkv8A6XrnwW1i6Lf2ZqgRrrwPcN/YmuiKyjhmss8hz/NcgzTDcGcaYl4rFYpyp8KcWThGlh+LKFKN/wCz8xs/Z4Pi/CU7LEYa6p5zTX1vB81aU41uPijhbI+KckxniL4cYL6lgMEoVePOA6dSVfF8CYmvK39r5Tzfvsw4Bx1Zy+q4zldbh6q/qGYqnh4QqYfJ+FPxY8NN4Zk+CPxth1HV/gzqmoz6loWt6ZAt94w+B/i2/HlyeOvAKSZa80e7cr/wnXgIsNO8UWAlvLKKHXoke96uJuGMwWYx4x4Onh8LxXh6EKGMwmIm6OVcY5XR96OS5246UsXSV/7Fzuzr5dWcaNaUsFJqjxcF8a5S8on4e+IUMVjuAsbiqmKy7MMJTWIzzw8zvEe7LiLhuMver4GvJr/WPhy/1bN8Mp16EIZlFSxEeqxfGX9k3xxNF4a8XrY2/ivQIb7QfGHhc6fr/wAO/i58P7yYT6XrVjZ63Y6p4f8AE2hSzBHl0zWdOur7w1rCzWV3FaXyCa4vDS4S8T8nhLMMrdWrlmNnRxuVZl7fA59wvnlKHJicJWq4Othsdl+MjC8Y4jCYinRzDCONWnKrRfLCcbT498FOIakMpzz6vSzrLaeIy3PcneGzLhfjbhmvU9pg8fh6GPw+MyvNsvnO0p4TH4WtiMpx3PQrQoYhc9X8R/8Agub8fPGniD9lm9fx34q1XxR4o+KPxB8BeCRd6hLCjReGvCiap41n0nTbGyhtNN0jRLBtB02G20jSrKy0y2+1kRWqvcSGT8g+kHSyfg3wlfD2R4ChluFzviHAYZ4fDKd67pOrm2NxOIr1Z1MRisRVqYLC/WMViq1avVvCM6jSgl+/fROr8QeInj5HizibNMVnON4Z4TzXGLF410+XDqusPkGWYPB4ehTo4TA4TD0szxzwuDwWHw+GoKNWdOlFuo5eR/8ABvt438QfCD4mf8FAf2VviBH/AGZrFx+yZ8TPE+lafJLmOPW7fUfhpb63HaO+wTJqGkzeHNUhKIDJbQzXGzaHavwzwmx+P4f4qyfw9zdfV8XS8TOFM4o0LtpVaGCzTD4zkk0larRxOX14tJc0It21uf0549ZVlnFfAnEPizkE1icDW8F+POHa+JilGUqGJzPJMXlyqwu2pUMTg83ws1eXJUlGN+i/o4/Z6j8J/C2HSf2p/Hi+ItXsfh58XvDug/DzwL4Vm0vT7/xn8QNJ0oeOL2XxDr+r22oW2geDPDuijT5NQa00691rXNQ1W003TRZRw3l6v9g8dSzTiSWJ8NcleAw1bPeFcdjc9znMoYmvRynI8Tif7GpRwOCwtShUx2bZhi/bxoKrXo4PB0MNVr4j2sp0qT/z68MIZJwdDBeMfEn9qY7D8LccZXlvDHDuTVMHhsTn3E2CwX+sOInmeZY6jiqWWZDlWAWGlinQwtfH5hisZQwmF+rwhXxC4z40eDfCttZ+Dfi98PL7X5vAnxiv/HdzBo3i8aY3ivwZ4z8La9ajxl4U1O+0aK30nX9PhPiLR9W8N+IrG0sDqOkakkGoafaalY3Pm+vwjm2ZVKub8K57RwMc54VoZNTqYvK3iFlubZTmWCqvKczw1HFSnisFXmsBi8LmGArVa31fFYdzoV6mHrU+XwOPchyalQyHjfhfEZnU4c46xPEdWngM8WEec5Dn+TZlQWfZLi8RgYUsFmWFg81wONyrNMPQw/1rBYpU8ThqGKw1VVOs/axXb4W/ZQH/AFZZ8NG/768Q/Edv1zmvM8MnfMvE3/s7nEC+7A8Pr9D2fGhcuT+C6X/RgOE39+acVP8AU+lfGQ/42i/Ckcgjx7+yuPQ/L8MPhp/hyPwr89ylr/iXHiX/ALEfiT+PEfEX+Z+tZ7p9MDgxf9VL4OLz04Q4T/Va/cfW/wDwSh/aQ1LWJ/ir+zv4x1SW+1v4WeP/ABLa+Hru8lL3WpeBNb8QazqPhG5ZnO6RtPhW98Oytzg6RbgnLc/zd9ITgenw1xDkvEWAoxpZXxpkuCx84U42pYfPsJgsHTzilFLSP1tVMNmkY6XnisU0uWOn9x/Rn8R3xxwjmuUYys55rwdneY5XJTnz1KmUVcyx39mTcpe9JYSpQxWXKTu1QoYNSblLmf7e1/Px/SIUAFACFlUZYhR6kgD8zQAAhhlSCPUEEfmKAPx7/wCCvXh3xb8Uvhx8NPhX4E1TQ9Q1PSfFtx8cvGHw1W9kTx94y+H/AMMdOubObVfB2iLE/wDwk1h4M8WeJfDuteKtMt5P7RhshZajZWt59jmir+lvoz4vK8k4pzDPc6pYjD4Stg6fDWAzudNPKMuznOq0atHDZjinJLA1czweBxWEwOIqqOHlVdShVqU/axkv5P8Apd4XPM68OnkXDU6OMzKNWrxBjsioVG87zDI8qpOhjcXleEiufMKeU1MdTxuOwtHnxPsYRrUaVV0ZRPxc+Evxd8PQeG7j4NfGa21DxJ8Edfv31SyvNLRLvxd8H/Fd4uz/AIWN8Nnl3BxJuB8YeDS39leMdN84iJdXw99/ZXE/C2Onj4cW8JVKGA4vwVBYatSxLlSyvinLaT5v7A4hjG1rWayrNrfWcqxHJebwulH/ADQ4J43yullVTgLjyjic18PMyxMsZh6+DjGtnfAuc148q4o4TlO6aldf25kP+557hPafu1jbPEN1jR/id+yh8TfD/iXw14isLgXNg+v/AA8+Ivh9RqngP4o+BNTH2eeeCG532mteHdYtW/srxj4O1bdc6ZctLpeqxRXMWn6hJWFxfDnibw7jsvzHA1qbpVlgs8yLHt4bOuG85w/7yEKsqdquEx+FqL6zlObYa1PEU1HE4acoSr0EsdgeL/Bfi7LM2ynNMNVVbDSzLhfijK0sZw3xhw5jF7KpUpU6vNRx+WY6i/qWe5FjeathKznhMZCNWGGxMug8f/Dzwn8SvCer/HD4G6ONEs9FijvfjP8ABW3klub74SXV1IEPjDwcso+2a38FdXumJtbsLJe/D+6kGja2F0pbW6tOHI89zThzNMNwbxpiZYqrjJSpcJ8W1YKjR4op01dZVmtkqWD4uwtJL2lO6o55Sj9bwl8S6kKno8ScM5HxfkmN8RPDjBwwWHwEY1+PeAaFR18RwVWrS5XnuRXbrZhwDjazapVrSxHDNeX1DMEsGqNahg/Cz4r+Hk8NzfBb4022o638GNX1GbU9L1LS4lvPGHwX8W3q+W/j74eCbP2izuWK/wDCb+BmZdM8X6cJZoI4tdjilve3ibhjHvMIcX8I1MPg+LcLQhh8RQxEnSyvi3LKLusjz1xtyVYWf9j5zZ4jK8RywqSlgpSjS8/g3jXK45TU4B4/pYvMeAcdip4vB4vCQVfPOAc6rrklxLwwp/xKFRtf6wcOtrCZ3hVOdOEMxjGeI/no/wCC2vw28QWX7V/7D/7LN9f6V4j0fxbfD4q6R4l8NXa3/hbx74D8beL9L8L6D4z0G4DM/wDZ9xo3gzxbHPZXqpqOkajDqWk6hGs9nK8n8y+MXE+D8ReJvC3hbBU8Thq6zfEPiPI8dT9lmOS5lUx2CwmIy7MqOkVWwuFweJrUq1O9DF4WvSxVCTpVrR/tH6PPBeYeEfBvjjxxmVbBY7CvIMHDhHibLKqr5RxHlFLKsyzHC5tk+I+N4fF47McDh62Gq8uJwONw1fA4mPtqF5eYftrLqv7H/wC2j+zP+134VLaV4Y+I+hT/AAh+LL26mO1ngOk/8In4iTUdmwO2p/DfxFZ3Vt5uR9t8F/aFO6357PGXKKHBnid4b+Iyo8uAxWLy3D5rUguVUsflEqVNV6klvKplOIpWT0n9QqarVnm/R14gxXiL4KeMng/LEe1zTBZfnGMyKnUl7SVfK+IKdaq8NSg38NLPsHXUnHSn/a1HSSaR/Rr8K/jLD4d8Lav4U8QeCfDvxX+GfjK90jxTfeD9d1HXdFay8UaTY3VnpvjDwj4q8LXdrrfhvXY9KvrzSb+a3+2abrOjSiy1XTrmO2tJbf8ApzOeGv7cxGW57lWc47h7PcFg6+Dw2b5dQwWOjiMsxk6eIxGW5jluYUquDzHASxFGni6EZeyr4PEw9vha9Pnqxn/FvDnGX+rOCzjhjPeHMr4s4XzLMMNj8bw/m+KzLLJ4POsup18Jg86yfOMpr4fMcozSGExFXAYmVN18NmGCqfVcZhavs6MqUXxL+KN18RX8MabZ+GtB8CeB/A2m3ukeBvAHheTVLnRvD1rq+of2trt/PqeuXmoa34h8SeJNU2X/AIh8R6vdyXmoywWcEcVpZWVrax9fD3DVLIY5jia2YY3Os5zmvSxWcZ3mKw1PFY+phaH1bBUYYfBUqGDwOX4DDXo4HAYWlGlQjOrOUqtatUqS4uLOMK3FM8owlDKct4c4e4dwtfA8PcNZRLGVcDllLG4r67mOJq4zMa+JzDNM2zXGcuIzPNcdWlXxUqVCnCFChQpUY+tftbLt8M/soL/1ZR8Ljx/ta38Qm/XOT7nFfLeF7vmHia+n/EXuI/wwmQr9D7XxsVsq8F1a3/HP3B7+/MOKH1231PpfxooH/BUz4Xp/d+IH7L456/L8MPhxjPTnj8+1fnmUN/8AEt/Ej75J4i/c+Is//NM/Wc/VvpicHrtxN4Qfhwfwr/kfJv7NvxBufhX+3f4R8QW8zQWXjnX/AIkfD3WApKpPLa+INQ8VeHnk5ALRS2eq20Zbol06DhiK38f8ihm/gxDHKHNiOGP9Ws7oyteUMPWw+GyjMUnuozw+Op1J66uhBv4U17H0ReKKmUeNmeZHOo44biXEcTYCUHK0XiIY3G4/COy05o4nL4Ri/wDqInbdp/2IaZeJfadZ3qsClzbRTBsjGHQNnPTv/jzX+dR/qyXVZW+6ytjrtIOPyoAdQB/Dz44/4KOf8FhP+C0/7YXx1+BP/BH34k+Cf2Vv2P8A9nLxVN4I179o/wAR2GmvrPxL1uzu9SsV1lfEN94T8caza2PiKTS9Q1nwh4S8DaHpFzp3hGKx1vx34jW+13T9HtwDpvgx/wAFbP8AgpF/wR1/bG8E/sb/APBd3x34D+LHwB+MWg6prPwo/bT8H6Qs6aDBpM09s17qN54R8GeGdU8W+H7LVmtNA8a+H/EXgGD4j+D7zWvD/iKDUda8K3tr/aIBgf8ABRf/AILY/wDBP34mftb/AAc+K3wE/bL8L3mm/DH4NXdtpHjLQdH+Jel3OhePdW+IUuo3cFoL/wADWt0Lr+w9M0yS5JtZtPvLKdrC68+GW4tW/rnwD4w8OMj4G4qyPjfNsrw0s+zuMa+V5jhcdiYY3KqOV0aUJTWFwdeHs3iK2IUG6sK1KrBVqbhONOov4c+lRwP4t8ScW8E514Z5JnWNr8OYP61RzXJsZl2ErZbmjx2MqXpyxuOwsnU9lHD+0jyVaFajVlQrxq0p1aT+f/ip/wAFQP8AgmV8WfDbfFjRv2kvhn8O/i8L6KD4ofDO18NfEay8K+Nry9fn4mfDA2/geex0S51Kdnm8a+A72a0gs79ptY8OzzwzS213+mcN+M/BPC+ZR4XxfGlDPuFpUJ1OHeIqlLMq2YZNRorTh3iT2mBp18XToQ93Js7o060qtGMcJmEac4wnT/AOMfo5+JXG2Tz42wPhxiuFeOIYmlS4v4QpVsmw+U8R18S3fi7g72WaVcLgKuIqfvOIeHMRWoQoYmc8dlc6lOdSlV+Qv2gf+C3HwS+Gn7KPxQ+F3wd8Z+Ffj14l8YpPF8J9DlsvFlm3wO+JOpRGOT44aBq2raBp0VkmjaclymqeD1ln0jx5q1zpEWr2S2sGqXkvgeKXi5wPhKNLivw94ohLj2Kp5T7TLsFiZYbMcmqRqOtSz+jj8LhsNiKeW2jXyfFJ1Mbgsf7GNJSwvtFS+o8EPATxNx+JrcB+LfA9al4V1PbZ9KnnGZYKGNyjiKjKmsNV4TxOVY7GYzCV85fNhOIMHajl2Y5U8TUrShjvYyr+F/8ABCj9sP4g6fovibw7Z+NtVHxG+FniW78T6Dq2q3Ums3Gr+FPHst3d6xpmtw6k88PiHRL/AFr+3rTxFpV+JrHUbTVoIZ41ZreSPH6PmcYPjzg/iDgTipzzaOExX1yH1qvWli5YfH1amLp4vDYtydejjsDmUcTiKGNozVbD161KcXZyjPo+ljw/mPhb4hcI+KPAsaWQyx+B/s2osDhqMcBHF5VRpYKtl+LwChHC4nK8yyWWCwuKy3EwlQxeHw9eE4uUYzp/0TePfAPhH4o+EdZ+OHwO0eLQ49CgTUPjX8ErKSS5uvhZNO4jl8deBUkLXms/BXVrtic4lv8A4b30v9kax/xJTZXtt+6ZLnmacM5nheDuM8XLGfXJOjwjxhWjGnS4kp043jk2cuNqWE4uwtJbe7R4gox+tYX/AGv2tKf8y8ScM5JxjkuO8QvDnAwy+OXwjiPEDw9w8pVa3B1SrJRnxFw7GTdfH8A42u90p4jhbETWCx3+wewr0f52/g54W8OftY/8F/vBnwx8bf27feDfh9oGifCTTL3RdRSO48IeJNf8P22gaV4hs4LxZrG4tfD/AMS/ite6/qWhEW0Os/Y9TjaWO6nMx/mHj3H4/F+PHE+fZOsE6vhvw3HNasMXh3UoY+nkGVUZ4/AVp0nGrRr4lZhi8HhsXec8JVp0p8jhR5F/afhZlWVYD6LfBfC3EDzL2PjFxjPJMPUwWLVHE5VW4qz7EU8pzPD068alGthsG8pwGYYzL7U6WPw9avByjVxHM/0O/bf/AGPbH9pb9lb9tTwBIEvPGP7PXwf+IPx7+H19bWrmW48WfAHxt4ettWtLK23vLH/wl/gK/wDG+gwQGSR459WsQ7yvAGr9Z+kTQr8R+GWR/wBn4T2mLzLP8gxeEwzcZVofWcizjHyoU5KK9pW9gnRioKHtZ8trXUD8F+iNjMLwh41cRvNscqOBybhbinL8wxqUqeGl9V4o4fyqli61OUnyYb626VeftJT+r0pSlJvkcn/P78Tf2/fG/jH9jD9mb4JfCHXPER+PXje+0rRfFl54Pu7pPF9lZ/DvWINH8Oabp0mnSx38WsfEPxFZ6TqgijIa50fTrq2uEez1Z1f8cz7xizbNPC/gPhbhrFY3/W/NqmGw2Yzy2rNZlShk2JhhcFh6ToSVaOJznG06GItB3nQoTpzTpYhp/wBE8MfR5yHI/G/xS444xwOW/wDEPcgo43HZRSzmjSlk1erxHgqmNzLFYiOJhLDTwfDmW18VheaWlPF4mlVpSVbBpx/WX9gL/go3+yb8VvCOjp+2v+0L4b/Zp8R+Bra5g+K0GsaF4qu/FXi240Jlglj+Gmh6R4b1a2m8ReKnRk+y61Np1l4V1AaiuoCdbKytNR/Rcs+kplsOC8H/AGhCkuP3iFk1bLsdDEYPLKWMiuSef5riVSvhcop/xsVhaCnjniVUwNGjCEXiYfkOd/Q4zqfiLmH9jzxE/ClYWXEWHzfLKmFzDOq2Xz5qsOFsjwUq/wDtuf1XbC4LG4jky2OEnQzPEV5yl9Un9PfH7/grh+wx8YvEmnXeifG74Z+C/BXgnwLpPwx+GfhGKTxnqF9ofgTwz/aT6Ha63q8/hqSXWvEF1cane3uraiWEJubr7Nbb7a2S5uPr+CPEPws4Vy+vSxniVlebZvnGcYniHiHNJUMww9HGZ1mLw6xlXCYSGWxjhMDThh6VHC0Lc/s6XtalqlR06f594meEvjjx1m2Gq5f4MZ9kGQcP8O4PhDhLJKeJyjFYjL+HMpWLll1HMMfUzmc8fmdapjK+IxuJv7P21b2NLmpUY1an1L4s/wCCtP8AwTcvv+ChngX4s2P7X/wpufh1pPjT4D6he+KFTxqunQWPhP4f+CtK124bzvCEdwE0/UNMvLWXMAbzYSVBQhz+b5V4i8E0vAfO+G63EmX0s/xOT8a0KOUzWK+t1K2Y53nGIwVOPJhpUObE0MRRrU17ZLlqR5nGV4r9jzvwh8S6/wBKLhvjKhwbm1bhXCcQeGuKxOeQeA+o0MPlHDHD2DzKrPmxscTy4LFYXEUK3Lh5P2lGXs/aQcZy+D9V/wCCjv7Ecfxd8GeLNN/ab+G0trofx3s/E0l9G3ilI4PD9x4g1tL3UmL+GUk+yDS9QE8m1GlMUg/dbvlH3nGXif4a5v4Y8S5FQ4wyevmGO4Ir4HD4OP172tXMKeW0JYfDQ5sEqftnjKEacbzUVNJuSWp8N4R+DfjBw141ZFxJmHAOf4DJ6HF9bGYnMary54enl9bO5zniJ+yzCpUVJ4OtOq/3Tk6bfu83un6I/te/8F2P2lf2tfjB8Dv+CdH/AAQj8WfD/wAdfFbxr4Bj8VfFb9qu50yPVfDPw9sRDKt9oXhuLxz4cudJ0geFtOFpe+NPGeqeEPFF22ra9oPg/wACaPP4k824m/zrvfV7vU/1ftbTtoeTfFv9qD/g4Y/4IQat8MP2hf27vjN8O/8AgoN+xN4y8ZaF4U+LVv4fg0+TxT8OtQ137XJHDYa/P8P/AIe+LfCevXtta6h/wiWoXMniz4aarqllD4a1200LVNX0eVgD+2z4X/FbwP8AGD4b+A/iv4F1qDVvBfxJ8IeHvHHhPUxiP+0PDvijSrXWdHvDGSxia4sLyCVoiS0bMUY5U0AfwL/8E7v2vrL/AINh/wBqr9rP9hj/AIKCfDD4mWXwH+LHxKvfij+z/wDtH+CPCM3iXT/E/h+OGLRdM11rNrixfxBoHiDwpYeGo9cg8MXmpeIPAHjrStY8Pa3ot0l017ZAGF+2J8Xx/wAHU/8AwUJ/Zf8Agt+zB8OPi14T/Yc/ZWj8Zz/FL9oPXPD2neHfE95L8R5fDE/i1tJjuP8AhIdF0HUdTtPBXhrw78NPD2q3Go67PPe69418T6FYaBpk1vYgHmX/AAUB/wCDZ/8AZr/ZK+Lfwu8D+Dfj9+0JrXhz4jfD3xb4lXVPFcPw4vLy38Q+EvEOj2F7plrJpXhPRoGszpOuWl5tmhkuhMrP53lP5af0X4K+D3D/AInZPn+MzLOs2y7HZNmWBwyoZfHBTozwePwlarTrVFiKU6ntfb4atBOMow5LKzkrv+VfpG+O/FHgxiOHnkvD+SZzgs5w2KlVq5rPMKdWliMLiI0pQpSwdelDk5K+Hk1UjKV3JppNI+Hpf+CGfwiORB8evijED08zw34Onx9cG33fkK/Y5fRM4afw8WZ/HtzYLLZ/inTfr3P5nj9PLjRfHwDwo+/Lmec07/eqy++9vxPqf9n7/g3/APgPqsEPj3Qfi/42+L/xF+GUl/4m8S/s9eLfCPh7S4PGfhfTyLuHxn4Eu9Gv7m58bL4SRBceL/hveWkWpSQKmrWza5o8Fxpl183hvAfh/gXjTLcVxbj8RmnB+Mq4ejlWaV8PSo5fhM8lJRoZdxZTU5xw2HxdTXLMap/2bicRyYPH+yvKM/scZ9KLi3xP8Oc5wPAWVYXJPELL6GLr55kmGxeIxObY/hiMObE5vwHVlTpzxmMwFK8c5y6VN5zg8J7TH5S675Z0/h7wYPhz+wB/wV/0dvHuh6jB+zV+0jbtZ3k/hlFTVvCOgfFq5W2XxD4TErR6dNqPww+L+lRX8ejS4tNV8MG40CZYYNYV0+V4sy/OvCjx0p1+Fq2GyzD8Q4ihj8toY32kMnxeHzes4YrJsydNfucGs3o1cKq9P95lqlhsdBL2KjL7bgHNuHfHj6MFfC8cYbGZzjOEcHisqzjFZc6VTiHAY3IMOquA4jydVZP6xmL4er0Ma8LVbpZxKnjctqyft3OH9QuraP8AEH9l34keEPGvhXxXaXWnXduvir4Z/FbwyDdeC/iL4GvH+z31zDFeK0F3pt5YtPovj3wJr0bXWl3BvNE120x9kvJ/7EwOP4d8SuH8wyvNsvqUeSpHAcS8O5k1SzXh7MqSVZKpOm4zo18O19dybO8HJU8RTjTxmDqpqrSh/nxmeWcX+DfFWU53kObUsR7WjPNeDOL8ni6+RcV5PXvh5OnTrKdPEYbFKTy3iLhvMIyrYStKtl2Pov8AcYir+Fn/AAQq1Q/HT/gqD8U/2rZtI0nR7b4k/tpeC7vRtM0O1e00HRLHxH8Yrnxm2iaDaySTyWejaVY6l4X0/TLMzS/Z7C1tIfMcKGr+QfDXCTzTIPHziqvi8Xmbr8O8S4GjmOPnGtj8ZGOV5ri518XWjCEamKqweBnXnGEVKpeaguY/0A8ZMxpZHxV9FbgbDYDL8mWF4u4NzPEZNlNKWGyzL6jzvI8DTwuBw8p1JUcHQqxzSnhqU5zlTpWpucuW5/Qr8NcDxj+2/ujSVf8AhQn7S4aKUBo5V/4WZ4VDRSqRho5VzHIpGGRmUjBNf1BxBrlfg/dKSfGvh7zRavGS/wBXcxvCS6xkrxkuqbR/EvCavnv0hrSlB/8AENfFlqcXaUGuLcnanF9JRdpRa1Ukmtj+fH/gnl/wR/svCn7Y3x4/aN+Pqaj8P/2Ovgp4y1SD4W+KLe0gk134o6r4ut217TvAfwjs53MeseNdE8NamnhO91Sdf7M8FyXl94g1N0fSbeOT+aMo8PMx4N8Ws7wOTZNTzXN1UxGK4Hw2JU4ZRgcpzGU3LinP8TDWhlOSYepLK6VKL+tZnmrnhcHDmw9ScP7Oz/xcyfxD8A+Gcy4j4iqZHkDo4TA+J2NwcqdTPs0z3J4U+TgjhbCTssTnvE2KowzuviJp4LJckjSx2YT5MXRpz+of2qP+Cdn7K37bv7RGofErRfghq/wy8S+OrjQvDOi/D34F61d6dFr01hbQ6Nodxqtg2nanL4r+I2s20Fu/ivxaq2c/ijVFl1W/tklNzezfs+afR/4ArYbE59xhm2cYrNVTxOacTcSVc0pZXhcXiZyliMbmFTCfV54TLsLTv7OjRotKnh6dKM/a4lznU/nPJPpW+K2GxeD4X8Pcg4ewORyrYPJeC+DaGRVs8x2AwVOMMLl2VUccsVSx2b42ty+3xWJxClKri6terTdDBxp06XMfGP8A4IPf8E9/gz4ctPh3eeIPjX4w/aFa+jvPiHdeHfi3pEvw7+EkSKhX4dW8sHg66Pjjx9Gc/wDCV6nBf2/h/wAN3DSaVapqN9C7p+d8LfR/4V4wzCrn1CnxHk/AnsZUsip43GRWe8Tzk3/wvThWwaWT5HJW/szDzoVMdmEOXFVHQozUZfr3HH0reO/D/K6PC+KrcIcReKH1iFfietluWyfC3BMIxTXC9OdDMJviHiWLf/Czi6eJpZblNRzwdGOJxEHKHGfs3/8ABAX9kr40/G3wH4GvdT/aAl8K3eswah8QNQ0bx5oFnL4Z+H+nFp/E3iW81m+8ITWGiWOl2gXdqeoIbdZ5IYEjnuJ4oH6fELwB8OuE+EM7zihmOfUsxp4SdHI8Picww9aOYZ5iPcy/LqWFp4CNfGVsTVbth6NpuMZTcoU4ynHi8J/pVeMHHnH3DnDuJyjhavk9bG08VxNi8Hk+Jw0sq4bwv7zNs3xGNq5rLDZfhsJRs3isT+7VSVOlGNSrUhTl4Xe/8ETP2Tbj4keD/CGi+MvjZPp3in4mzeGorpfGXhu5lfwxbvrFzLqFrcL4PEbzvpdjazQ3ex4HM/m+UUdQMONvo+8DcMeH3EPFMcZxLHMcp4djj6WHxOOwrof2pVjhaNLDVqP9nwqOmsbiVTnRU41LLk5002e34SfSl8SfEHxTyjg3EZfwg8lzDO8RhJ4vAZbjY4t5ZRxWIaxFHESzSrS554DDyqxrexlTlf2ii4ux9aTfs9Xv/BsB/wAFHfg1+2lpfw3+MPx1/wCCdnxt+Dll8NvGXj3ytI8ReOvht4l1+fQb/wAV6BqWqW1j4c8PQ+JNO8W+F9I8XeBdP11vDen+OfBep6j4d07WJPEfh/Urm1/itn+hy1Sfc90/4LB/8Fsvhr/wWo+Cnhf/AIJf/wDBMH4T/Fz4yePP2gPHnw+1b4g+NfF3geXwboPg7wv4I8R2Hiu0s7a2nu9S1O18jxPp+jal408cazHpHhXwx4Y0i/gtbjXrrW0fTQD+zT9j39mi5/Z3/ZV/Z3+A8mvXd1J8Hvg58Pvhu943nRm+fwf4a0/Q2vzE7h4Pt7WRvPs0gElt53kSAPGwoA+ifiR8JPhX8Y9CHhb4ufDXwB8UvDAuFu/+Eb+I3g3w3450D7UgKpcf2P4o0zVdOE6qzKJltllAJG/HFAFjwD8L/hr8KtEt/DPwv+Hvgf4ceG7Tf9l8PeA/Ceg+D9DtTIQZDbaR4esNO0+AyEL5hitkMm1d5bauAD8hv+C3Hw0m1P4M/CH45WUDSN8FPijDZeJZkTJt/AnxWsk8G6xdysBlbXT/ABGnhG7nZjsiQPKcBSa/qL6KvEcMu42zbhytNQp8UZJP6qpS0nmeR1JZhQgk9HOpgamZRj1k0o9kfyF9MzhCpxB4Y0M6w1OVTEcMZpGvPljflwOZxhhqkm+iWPo5cnfRKbfc/ALBBIPUEg/UHB/UV/fy2P8AIxO6T76nonw98NfFq91AeMvhR4Z+I2o6n4EvLXWz4o+H/hzxJq1x4Sv7QG6tNQl1TQdPvI9LuIkVplW5dfNtTIJoZrOWZH+fz7MeF6VB5RxNmOQYfD5zSqYP+zs8zDL8LDM6NX91UoRw+Nr0pYmEpNQbpp8tTl5Zxqxi19TwvlPG2IxX9vcF5TxVi8Xw5Xo5g844ZyrNsbUyTE0F7ajiamMy3C14YOrCKdRRqyXPR5+enOhKcZfnj/wXK/Z/8P8A7XH7GurftteAtFs/Bvxz/ZH8R+G9Z/aD8P6LYGx8NeLPh98XPEmneCJfix4Chsvl0HV4viEPC+peO/BCqlhY3kmreLtBeC2utRta/jn6QfDmY5DlXDmX1J4jNstwGNx0uDs4qVXWznK8sp4Wnic04ZzmbarY7CZZClhMxyLOk51YYSlicFjk5xpVz/Qv6JvGGT8VZ9xfm9Klg8gzfNstyun4icP0qEcNw9nudVcdWweR8Z8PU4xeHyzH53Vr5hlHE/Dj9nRrY/EYTMcsfs5V8NL0i7/aqj8W/wDBBv4J/Ho3qL4m8N6P+2TZ6xH5mx7Xx/Ho3w48LBACQUa68VX0d3b8AutzE/JkDN9Vwlx+sxyHxR409pH65h/Cng6lXkmouOc0MNxRlEoO/vKX9ounKmnZqnOnZWat8Lx/4UyyjinwR8OPYy/s/GeOviDWwkbcynw5i8ZwTxBTqJJuLisojVhUa09rTrKXvRkeZf8ABvp8I7z4ZaD+yH4g1O38i++K3xz+HHxKj3RlJTpWr/Fe18N6I7FuXE2l+C7W8ibIHk3ibcj5m5PCPB0qf0eOPsZTglUxmU8eRqz6zqUMoq0L3tolTo0opa2V+53+PuYV630ufCrAVJuVPA594XSw8OlOnieIKGJa3ablXxFeUn106p3/AGT+G3/I4/twf9kF/aX/APVm+Fa/bs+/5Ffg9/2Wvh7/AOs7mJ/NXCX/ACPfpDf9m18Wv/WsygxdfAP7EfwyJAJ/4at+L3JHPPwo8A5weoyODjqODkV1YLTxg4it/wBG14WbS0TtxPna1Wzstr7dDhzPX6PnCF9X/wARm431er14M4bvr59e/U6ax1+L9m74G/DPxl8PoJU+Mv7Rnhfxzf3HxOuTEt/8LfAOheMNS8CXnhb4awJvbS/E3i17Ca58QeO5JE1S00qYaPocdmXe7Tz62Cn4g8Z8QZTnlSL4T4CzLJqNPh2nzOhxHneNyrD51RzLiCcrLE5flka0aeByWKlhqmJh9axkqqSpv1sNmcPCjw74Tz3hmnOPHnink/EWJq8X1eRYng/hrLs8xfDmIybhOnFSlg82zqWGnWzLiKcljKGCn9Ry+NBt14/PXwo+E3jH4z+Lo/CXhCC0SSKzutc8S+JNcu/7O8K+CfC1ifN1nxj4012fMOkaBpkZeW5u53a6v7krZWEd3qNyiH7zifijKuEcqeZ5pOrJTq08Hl+X4Ol9YzPOMyre7hMqynBQtPFY3EStGnSglTo006taVKhTcl+X8F8E57x7nkckyOnQjKFCtmOb5tmNf6rk/D+TYe88fnufZjU/d4HLcJDmnVrVJOtia1sPh41sVWSPY/ij8XPBvhPwdffAD9nWe8T4cXMsB+J3xSu7U6Z4u/aB1yxJCz3kWftPh74U6ZMZP+ES8DrIv26E/wBreIRPcXUsMvyfDXCua5pmtHjjjyFJ5/TjP/V3hulU+sZXwPhK1rxpS/h47iXEQUXmecOP7mf+zYHkhSjOP3vGHG+Q5JkWJ8NPCyrXXClaVP8A1v4xrUXhM78TMww7ajUrw/i5ZwbhJ839i8PxkvrNOX1zM1UqVpwn5B+y74MuPiX+1V4H0y3haez8DabJqd4VXciaz4snjsbCMnkCWDRLHUboj7ypcxtwGGfzr6UXEcMq8O8NkMJxWK4rzvC0eRP3v7MyO2Y4ybV78k8W8toXejc2t0fvX0HuEKmY8cZvxbVpP6rw9ldeFGq4+79fzJSy7CxTtZy9jUzOqtdPYJ2P7Lo/B3h/V/BMfg3xLomk+IfD19o8el6toWu6bZavo+p2TRKstnqOl6lBdWF9ayY+e2u7eWFv4oyRX+eZ/qacd8NP2df2fvgu16/we+Bnwe+E76nIs2pN8NPhn4K8BnUZkfzElv8A/hFdE0n7bIkn7xHufNZJPnUhuaAPZKACgAoA8u+Nfwr8M/G74T/EH4TeMbUXnhr4geFNa8LavEFBlS11ayltvtdtkHbe6fM0OoWEgwY760t5QQUBr18gzzH8NZ3lPEGVz9nmGTZhhcxwjbajKrhqsansqlv+XOIgp4euutGrUT0Z4/EGR4DiXJM14fzSn7TL84y/FZdilZSlGliqUqftqaentsPNwxFF7qrSg0fxTar4P8W/C7xf4x+DvxEjaLx98Kdel8JeIpGRkTWrW3VZfDnjCxDYM2leMPD7WWtWc6/IZZrq3JEsEir/AK2cOcQ5bxZkGVcSZPU58vzvBQxmHjzXnhqkk4YrAVt+TEYDFQq4StF6qdJy+GUb/wCEniVwRmfh7xnnXDOa0nCtgcdWhCai1Tr03JVKdeg2kpUMTRqUsXhmtHhsRS6xkl94f8I/8YviV8M/gDJ+zV4mubTQPh94Dh03xhoXhz4n6P8ADzUPh78aIvEevah4s+IHje31DxN4bmFr4ogn0LWtG+IEiajp8Gh2Y0JZ7OTSZdPn/LPr3CnD/EPG8fEHL4VcdnmdTxGVYzMOHcXntDPOEpYDBUMsyPJ54fL8fB1MtnDG4TGZHGWHrzxlX664VY4qNeH6sss484s4R8NZeE2b1aGWcMcOU8JnuXZVxdgeF8Vwxx7DNcxxWdcT8Q0sVm+V1PY5xTq5dmGX8SzWLw1PLqCy9VKE8HPDVJ/jFafDj4yeBv8AgpzoMMuj+JvBHj/4Q/Ajwp4z1jRLVLbQPGGt6h498E+GPin4u0C1EUKJpniXxg/iXxDpM8cECXTXUWrQwxrdxgeBDh+tXwngvw/xJhMRSoY3HeJOAnluPm62Oy/IMz4Wz5ZTleLqSlNvGZXkVfBYSonOcqFShHDynKVBs+qq8V4bDY/6R/FvB2PwmIxWW5Z4OZpSznK6aw+W5txXkvHHCrz7PMvpQhSjHLs64owuY46m406dPE0cVPExpxp4lJfwDeLvjz8Q/gB+yz+09/wTf8Y3F00ug/tA2+teFt32ojE9/oVt4/Fqj74otO8UW3w4+G/iSyjR1W5Gp38qozXDlv5Cr16/AeV+Kfh/jXUjmmZZnw/lLUYSjGvhsizbG4qvWi9fdxUHgqtJP+JRrNo/0BwuFwnilnfgb4s5cqU8jybJeK8/i5VYynhcbxPkGXYHDUJJpe/gqizKjWa/g4jCpOydz+3T9lX4cW3wh8c/8Ez/AAJbW62q6B8Jv+Cf8U8YGP8ATZNK8ISanM5+80lzq0moXcrn5nmuHY5Lc/1XwBljyj6PnHeWTd6mDo+KeEqPr7TDYXFUJr1U4ONtdj+F/FXOY599LPwvzqmlGjmWJ8D8fRSeio43G4HFU3fezhWjK9tb6Hpvw248ZftwD/qg37S//qzfCtfpGff8ivwd/wCy18Pf/WdzE/HeEv8AkffSH8vDbxbX3cW5QjF17/kyL4Zf9nW/F3/1VHgGurB/8nf4i/7Npwt/61GdnDmf/KPfCH/Z5uNv/WL4bIPjzIYvgB+xXKACYvg98XpADnBMfxz8VOAcc4JGDjnHSq4KV+OPFyO3NxVwtG/bm4My5X/Ez8SZOHhn4BTSTcOBuOZpPZuHiHnErO1nZ2tofSvxL8H+H/Aek/ET4D2uv6n8Mv2efg9Y/CbWPjb4w8P6TaeJPiv+0H8VPiX4csfEPg/Q5rO4vdE0ttPsPO1YeHvDF5qdt4M8H6T4f1DxJqx1fVLmzjH59w/muOzrFZDxrVwWH4i474rrcT4ThDKsdiauX8M8DcNcPZhXwOa4yNWnRxeJ9tXUcL9fzGlh6mbZricdQwGF+q4enWk/1ni3I8s4cwXFPhvRzLFcI+F/AuG4Kx3iBnmW4Khm3GnidxlxZleGzPI8unQq4jL8G8Ph3Uxv9mZRXxdHIsjwWW4nNcb9exdXDwj8SfF/wT4D8H/DjTfjZ8PPF3iLxN8Lr7XtX8H6tb+MtA0/w9498H+N9J0q016Lw5rNloep6voWtQeJdFvY9Q8Ka5oV4ItQkhvtNvdPsNQsyk361w9xBm+KzfG8McSZbgMtz/CZfhs4w9TKsdXxuTZtk+KxNTAvG4KtjKGExuEq4LG0nhcwwWMpc1B1KGJo161CrzQ/DuIeCso/sjJuKeBs3zTO+HM5zrFcM16GfZZhss4i4f4jwuCpZo8BmdDLsXj8txuEx2VVnmOW5pl+IVOvDD4zDYjDYfFUOSp+mv8AwSG/Zw1W0S/+Kfi+w8nW9evpPEOprImfst5eRxx2OkI5HMehaVFaacApwLhLtxy5z/n1478e0uPOO8XVy+t7bIOH6TyHI5xb9niaWHqynmGZ09bcuZZg6tSlOyc8HRwb2sj/AFz+jz4arwz8N8ry3FUPY53m/s85zqM0lWo1q9GMcFgKvX2mBwfL7eL+DG4nGLpd/wBDoAAAHAHAHsK/GD9zCgAoAKACgAoA/Fv/AIKn/sPav8V9PsP2iPgzpCXXxi8BaTJp2t+HYClv/wALS8AxyyXtx4VmlbbGPEmizvPqfgi+nOFvJrzRJnW21OA2/wDRvgB4vU+BMyq8NcR4iUOEM8xMav1qd5R4dzeajSWZ2SclluMhGFHN4w1pclHMIq9HEKp/Ln0mPAqn4p5As6yPDx/1yyPDyWHhTjGNTOsvpudRYFN2Uswwkp1J5apySxNOpXy6UlKrhZ0v529M1DTPEFnHfW8fmBZJ7S4t7+z8jUdMv7SUw3+lanZXKC507VNPuUe3vrC4SOa3nRgyldrN/onGbSjKnUvGpGFSE6NVSp1qdSCnTq06lKXs6tOpTkp06sHKE6clKLcWf49ZjllfL8XVwWY4X2WLw0p05069H3ouE3GXKqsFOKU4yjKLUZQnGVOpGNSE4R+tfgu+PgN+2jHn73w0+DL49fL+PvhMfp5nofqO/wCb8Xx/4zXwlfbiDi1f+BcEZk//AG0/VuAZf8a38e4fzcJ8BS/8A8Ssm/WX/BR/Nh/wVD/YUN98c/2IP2ldBtxNoP7UXxO8QfBz4j2qRDy7Pxh8BdT8HaqmqTsQN48UfCnxDZ24HzM9z4K1OaQYbLfy74ycMyzbx6yOhh8GvquZR4L/ALTrQhaE8RVnjnJ1mt6tXLcnq8t1eVPCTd3ys/tr6O/GkMh+i1xPiMXmEvruT1PEiWS4adS9SnhaMMrUI4eLfu0KGc8QUHK3w1cfTjoqkLf1TzQrZ/tUfsMQooQQ/Dz9gIYA4Dtp3g9pMBun7x34+tft2WU/Z+FHi1Tsk1mnjUmul3XzJ2t6yZ/NOdVvaeO/gLXu25ZF9HCSe70oZLFO77pa99Tj/hv/AMjn+3D7fAf9pgfl8TvCor6LPP8AkVeDv/ZaeHn/AKzmYnyXCatn/wBIhf8AVt/Fz/1rspMTX/8AkyP4Y/8AZ1nxe/8AVUeAK68H/wAnf4i/7Npwt/61Gdnn5n/yj5wh/wBnl43/APWM4aK3x+/5N7/Yw/7I18Yf/V4eK6vgn/kufFr/ALKzhT/1jctMvEz/AJNh4C/9kHx5/wCvBzo9z/ae+KWleBf2lv2gPCvjTwpF45+GHj/Q/gsfGPhsa/L4S1az1Hwj8LPBWp+GPGXhbxZFZ6kvh/xJ4alvtUiSe+0zU9H1HSNU1PS9XsZbadJYPjfDzhzEZv4ecE5rlWaPJOIchxnF7yzMZYOGZYSeGzLiTN6GZZZmeXVK2HWNy7HQoYac40sThsTh8ThsPicLXhUhKM/0fxb4twuQ+LviTkOd5F/rPwrxVgfD6nnGTU8fVynMYY7J+D+H8Tkmc5Fm1HD4yWAzrLa2KxdKi6uCxuDxuEx2KwWMwtSlVjKn5H8JvC7fth+Ifh/8P/hb8ONT8Afs4+AfGV9480fT9f8AEM/jLxV8UviVf2drocvxO8a6+2kaDYSaL4a0SyTRPAGhaVoOm6TCGvtWZL17gXDfk3jRx5iuEJ51kFPiOln3iHxDlWHyPiHNMswMcpyzg7hWFSpi3w3lGDjisbXpZtnNbETxOa4jFY2vjKGGlD2n1erPDUqX9QfR48LsDn+X5DntXhCrwvwDkGbYviLh7J83zN8QZ3xZxXiKNDBPiPPcylgcuwtXAZPhMJRweW4PAZdhcA60KlOk8VBY6vW/qh+Dfwx0n4VeCdI8MaZAkZtbWJbh1UBpZtg3uxHUlsnJ59eTX8bbaLRLRJaJJaJJLRJLRJaJH9076vVvVt6tt6ttvVtvVt6tnq9ABQAUAFABQAUARTwRXMMkE8aywyqySRuAysrDBBB4OQaAPw0/b4/4Jht431vWPjl+zs+n+FviXeL9p8V+HbmORPB/xI8hMIfEFtaKZdM8SJGvk2ni/T4XvCCkWsW+oQKssP8AR3g/4/ZhwLSw/DfE1PE51whCShhJUWqmb8Oxk7v+znVlGOMy2LbnLKatSDo3lLLq1Ft4ep/Lfjt9GfIPFOniM9yT6vknGXLKpOu4+yy/OqiirPHSpwnLCZhLljF5jGnUpYpKMcxo1JKGLpflZ8K4/EXhj4Yftr+DvH/hXXfh/wCMdL+FnwifUtA8R23kxtGf2iPAlnDfaNrcedH1/S7m5mWG1vdOuWaR5EilghlbZX9aY7iLIeKs98JM44czbBZzl1XiTieMcRg6t5UakuBs4lKhjMNNQxWBxUErTw+LpUqsbNqLj7z/AIEpeHXF/h5wp48ZPxRk2Ly/Ef6ocHKi6tJqGJhS8SuHpOth5wc6WIoOm5TWJw1XEYZxTarXUoqPx9YWOofsi/s+RahY2t4tv8c/2k54UvLWG4NvcroHwaVLi38+N2t7gRTyRrPD5cwhmliD+VNIj+pltGlW8UONVWpU6qjwn4fVIKpCE+SaxfF8VOHMnyTUZSjzx5ZcspQvyykn8XnGIr0PBLw3lh69ai5cf+LNKboVZ0/aU54LgCo6dT2coqpTcoxk6dTmhzwhPl5oQcfb9bf/AIyt/Ynf/qQv2DGznj5bXwkvJ/DrXzGEj/xrTxdT0tnfjUv/AAKpmb/rufbZhL/jc/0f5L/om/o3vf8A6c5L1/qxxvw448aftxj0+BP7TX/q0PC1evnv/Iq8Hf8AstPD3/1nMxPC4V/5H/0iP+zb+Lf/AK1uUGHr/wDyZH8Mf+zrPi9/6qnwBXXg/wDk7/EX/ZtOFv8A1p87POzP/lH3hD/s8vHH/rGcMnNftLeIdL0L9n/9iiC9mkfUb/4O/GCHTNGsYJb/AFzVrhvjj4sVLfTNJtVku7qV3ZE3BEgjLgzTxLlqfB1ahhuMPGHF4qtRwuEwvFHC9fFYvE1qeHwuGow4Nyznq4jEVpQo0acVduVScVo93o/Q4zyPNuIPD76PuX5PgMTmGLxXBPGuGo0sNSqVpVK1bxEzqNOlCNOM51Ksm/dpU4zqys+Wm7M+jfil+y74p/bG/a18beINIu7fVvg/dL8N49Pg0gXJsvElxovwy8EaTq0vibUXSHz7DTdc07UdPTQbDdY3ktibm9u7qB44n/k2X0gK3DHh/lnB3BdKdPPqcs8jmPEteFN0ctp43iDNsXRjkNF86xONqYXEUaizLERWHwjn/s1CvXXtqP8AoBg/ow5XxB4oZx4jcbzp4vL8TT4ceWcO05T58RPLeGMlyzEPNaqUHhcKsXgq0J4Ki3jcXFONethMNKVGv+/P7Nv7M/hT4D+GbSysbO3fVmt4luroQxoQUjVBHGEUCOONVCRxoFSNFVEVVAA/mOrVq16tWvXq1K9evUqVq1atUnVrVq1WbqVa1arUcqlWrVqSlOpUnKU5zlKUpOTbP63pUqVClSoUKVOhQo06dGjRo04UqNGjSgqdKjSpU1GFKlShGMKdOEYwpwiowiopI+pazNAoAKACgAoAKAEz9fyP+FO3p96/zFdef3P/ACF96QxrKrqVYBlIwVYcEEdCD7evNAHzR8cP2WPhT8dPDWv+GPFug2lxp/iWxjsNas2jYWOq20F9banawajDGUS4W21WzstTtQ5D22oWlre25juIYpV9TJs6zfh3MsNnGRZji8pzTB1HUw2OwVT2VelN050ZNNqUJqdCpUoThUhOE6NSpSnGVOcovy85yXKeIstxWT57l2FzXK8bTVLFYHG0/a0KsFUhWimk4zg41qdOtGVOcJxq04VIyU4RkvyR+NX/AASs8d2fwx8IfDL4M+NbzQfDPgPxt8RPHOiw6jG/jGS6uviNYeD7DUtHvl8QXbXMWjaUvguxm0SKwvobi2k1DUknluY3t1g/eeFfpI8UZNnmY55xFlGW8UYnNMryXKcXVpzeQ4lYfI62ZVsNWp/UqFfBzxVV5pXjiJzwkKdT2dFxhTkpuX838c/RR4D4q4eyzh/JsXjuF8NlGcZ7nmCpwi81oLGcQ4fK8Pj4TdbEYXFqhy5RhHRX1mrUj+8U5VE48viHin9m39pnSvjx+zd49k8KaPeeFfhFoH7MHhzxgzWOsQ+INQb4LvoVv4x1jw7Z2M15prw6vDptzeeG9LvbqGZC8NnqNymWnr6zAfSE4VXCHHOQ4zIuIcNj+KcZx9jcHPDyyzF4LDS4uWLlhKGJqyxGFrv6pLERhiq1PDuM4qU6VNu0D8/zX6JudVuO/DrirL+JcrnguCMD4Z5fiKGIWMoYrF0uAngY1q1GH1LEUr42nhJSo054qMlKahUlBpzOB8FfAP8AaZ0nxT+09f6l4B0uCw+L/wAMvjV4K8DTWSa9qF3a618QPHGia/4ZvvE9rcR6dHbaVb6Xp1z/AG2mnXN3exX0lvDZJPD5ko9LOvpE8F4rLuAsPg8p4mq4jhbPeFs3x8auHyzDU8RRyPKMVgcVRwdX+0K79tVrYiLw8q9OEHSUpVHCVoHj8O/RE4my/N/EvG47iLJFhuOuGuM8gwvsa2MrVMJLifPMFmdCvXissglChRwsoVVTnVkpyXJCoryXdeHP2Ef2iviJ8CfBvwU8US6joh8P/GLxr8U7zxN4WWHw4mo2fi7wh4Z8KweF1t7uLVdQtI9MOgzalLrEWoJdXrXqWot7ZLUSy/I5r9JTMI8WZpxPwxwxgsHPMOGsq4chTz/FVMzlh45bmWOzH68qOA+o0atStLGqmsPUqyp01S53Oo58sP0DIPoi8L0OCsn4N4oz3GZrhsp4szjixVMsw8MGq+JzfKstyqeEc8d9blCnSp5cqntlh+abquMadPl55foR8Gv+CaWk6Honw+0r4hatJrWnfDXQ9S8PeD7G5Ed3d6Po2t+Ir7xbrVj/AGxOkmrXq6p4j1K91W9kvby4aWeUIvl28MEEX4VxJxnxLxbjszx+eZpWxE84xlHMMwwlD/Y8rr4vDYSlgcNWeV4ZwwXPh8HRpYejOdKdSFOF+d1JTnL+kuGOCeF+DsuyrLOH8ow2DoZJgq2XZbXqRWKzDDYPE4qrjsTQhmNeMsXGniMZXq4itTp1KdKdSduRQjCEf068E/Drwn4A02HS/DWkWmnwQxqgMUKK7BVCjLBQTwBXy59UdxQAUAFABQAUAFAH4pf8FOPjv8RrT4sfBz9nj4bfELWPhzF4g0+PxD4y1zQNduPDs8w8RaxNoOg2ep6pa3dhcQ6Zp1rpOtarNai+tYLu4uLJrmTbBGU/rLwE4UyGjwdxr4i5/wAOUeJ55Qq+HyjK8RgYZhKrPLMFHHYpYPCzo4iM8XjMRisFg6dX6vWnRpwrOEHzTUv4L+lTx5xTiPEPw48IuFeL8TwXTz6WFxef51hc0qZRClTznMpZXgZZjjqWIwk6eX5dhcHmOY1qP1vD08RUlh1UqR5abj4xbfsk6rp2r6dLp3/BTrwnZ+KHurNrS3f4o6g9+dTaaJoLZPK+J0xmma52xIpgmWeQgGCVXMT/AFL8U6mJwdZYr6NeInlyw9V1+XJ4+wVH2UlNynLhCnGNOML89SM4OMU5KUJRTj8O/A6jg8ww8sD9MrB081eJo/VufiGpHEyxCqx9kowj4hVZTqyqcqp0p06kZyahKE1KzxP+Djb9vX4r/wDBPH/glbe33w7+It14d/aO+N3ijwX+z/4O+Inh6R7HxFoVxq2man4l+JXjnw5NAkMul6rbeCPC2s6XpWvW32W80DXPE2k6zpz22pWtmyfxLJqUpSjFQjKUpRhFtqEZSbjBOTcmoJqKlJttK71bP9KacXCnThKbqShThCdWSSlVnGKjOpKMbRjKpJOcoxSjFyaikkj43/4Ntv8Agq/rfi7/AIJOftH/ABY/bg+NniLxba/sNeLvFLeJPib8Qtbu/FHjmT4Rv4P0vxn4bsdR13WLqfW/GOtpqNxrXhTwhFqN3e65q1z/AGJ4at5rqQWMQRZ/Knpn/Bf7/goT8Vf+Csfwz/bGg+LfxO8BfCjxZ8dfC3gzw9+z9B4n19vgrZ/AG48b6RoWpfC6+8IiaDwd4p1hfDOqx3XivxfJpb69N47uV8VWlxpU8Oi29iAf6x0us6ba6LJr2oXtpp+kW+mtqt5qF7cw21jZ6fDam9ub27u52jggtLW2SS4ubmV0ihgikmkZURiAD8Yv+CeP/Bd/9gr/AIKb/tAfGD9m/wCAd745sfHvwyj1nXPDM3xB8NaXoei/GbwDoGp2ejar48+GdxZa3qt8+n2d9e2d3LoXiyw8N+KToGp6brkekPANZg0UA+v/ANp39v8A/Zj/AGSPj1+yL+zh8W5/EUXxM/bT8ceJPAvwfsvDXhhNesLa+8LWukSahq/jK4jvre60TQptT8QaD4fsbqysdXu7jV9VjdrCPSrDV9SsADwz4X/8Fpv+Cf8A8Y/27NX/AOCefwk+JWrfEH436BpniK51fxB4O8K3Ot/B6y1zwmkb+IvBx+Jlhcy6XceItIaVbO8ns7S48Lxa3nwwPEreJwNHIB4H/wAFAv8Ag4b/AGH/APgnt8ftY/Zd8a+EP2ivjZ8cvDfhnQPFPizwd+z78ONE8Xx+DrTxNYwato9l4m1XxD408JwWuqXOiX+j601nY2+ora6drekSXc8E16kCgHt3/BMj/gst+zb/AMFSn+KenfCL4d/tAfCXxL8IYvDl34n8O/H3wBpfg+e907xOurmw1Hw9qugeJvFWi6lFanRL1dUtLi9sNSsVNtcGzltLmO4oA/MHxT/wdzfsHW3iDxdY/DD9mf8Abv8Ajh4Q8Fa9q+h6v8Tvh18HfBcvgeeLRHka81uwudW+JdnqkOky2Ef9r2n9v6boOoHS5Ibq+0/T97IgB/Q9+yN+1p8D/wBuD9nv4dftOfs8eK/+Et+FfxL0uW/0e8ntW0/WdK1GwvJ9L17wt4m0d5JptG8U+GdatLzRtc0t5Z0hvbVpLO6vtPns765APw5/ao/4Onv+CdH7N3x48S/ATwp4X/aG/ai1n4d6re6T8UvGX7OHgfwz4q+H/gu80u4+x6zaQ+IfEXjPwz/wlk2iXcdzbanf+G7a58MpcW81taeI724hmiiAP2+/Y+/bB+AP7dnwC8E/tKfs1eN4fHXwu8cw3S2d61pcaVrOia1pc5s9e8KeKtCvAt9oHifQL5WtdT0y6DKVa21HT7i/0jUNO1G7APpygAoB6an83n7Yvww1T9o7/gpHq/wnsdRSwDeH/AOjPevGs32PTrXwrZ67emGGXETSmfXpCPM3RIpeZ0l2eVJ/dnh7xjR8Mvo74Piz6k8diq2cZlHB4T2kqFOvmOPzargMK8RXpxlUpYajSwMq1eVNOrKFL2VK06kZR/y98XPD7EeNH0uMw4E/tGOV4PD8P5NPMMwdGOKq4XJ8qyGhmuOWEwtSUKVfG1q+aRw+Fp1pxoRqV1Xrc1KnOE/qe8/4Je/sb/CjTrDVfi/8WtU022mdIhc+KfF/hfwVo9/dAxFra2S5htnuVy2HginkkeJwX8vk1+Z0PpCeN3FFWthuGsrwM6yi5ShkXDWMzXFYWLTSqc9evj/Zyja8KlWlbnS92Wx+zYn6JX0a+B8Ph8bxlnma0sNKpGCq8T8aZdkOAxs4uLlR9nhMHlPtITulUpUKvNySdpRXvH82f/B5aVvV/wCCT/7O3hu+vJPC+v638bri3nF4NRe8In+A3gbw/eG5yyX1xa2Gv6n9mm5RkvXCHY+K/mKpKpKpUlVcnVlUqSquek3VlOTquS0tJ1HJyVlaV1ZbH9sUY0oUaMaCiqEaNKNBQfNTVCNOMaCpyvLmpqkoKEuaXNGz5pXu/wCU34+fCz9oz9m79rb9rf8A4JIfA/xn4wHw4+Kf7XPhX4YXfw3kmilh+Jl34A8e6tB+z/feKJ0sTdTDTbbxpZa5dtafZdO1C5Sy1fUbS4bRdJaxg0P3P/4K2fsS/Dn9jD9s/wD4IF/saaBp9rZeDPCng/4Vad4u14Rx28vi/wAV+K/2rINQ8feJNXfaEfVPEGqSC7u5JARANQhs4glta20UYB/V3/wclftl2v7IH/BKL4seGtB1+30L4p/tSWulfsufDGBr0WdyIfiLa/Z/ifq29AJrGx0L4TW3i5JtYXybfTtW1bQo5J4pr22VwD+bXwlo37HX/BOj/gsr/wAEJrX9lD4wfBvx1ba38AdI/Z5/aPuvhF488IeN4L3xj461Txt4Ui8X+OL/AMGalqen2/iPxvrXxCt70xahdHUZrbwxahoIrKCwyAWP+DwTVfir4n/4KD/sjeCPgi/i2b4hfC79jP4ofGE/8IPe3en+JNC8M3Pi34g3vjXX9Nu9OurbUo/7O8D/AA41zUtYGnOL1NDsbqSISjcqgH9Av/BtX+yp+wD4S/4J9fBT9o79lrw3o2ufET4m+FbCz+NHxD1pbTUviPafFTQFjs/Gvg7xDfMrT6PH4a8RNcyaD4eshZ6Ja6Jc6NrOmWlxJqR1vUQD+Yr4KXf/AAVy+P8A/wAFuv8AgrH8aP8AglrH8OdL8WN+0H8UPhN4x+Lfxl0PwZq3hvw54R8G/EHUfC/gvw5pFz4y0LxV5eqzaJ8PrK5kg0bQtQEGlaNZy6ibOP8AsvzwD+xb/gnN4X/4K4/CTwj8cfEf/BW/4y/s7fGDR08Ltrngq++EPhLRPCuu+CNO0PSdavfGVprOr+HPA/gDR9a03VrSOymtIH0K4utMk0y4un1uWG7i0+AA/gr/AOCVf/BWL9qz4Efs26t/wTb/AGJPgz8M/C/xs/bK+MXju+8G/tIfHX4g6V4X8MaRpnjiw0vwUun+D9F8UWuh+EtU8ZWC6Pdabp+sat4k8SW8muxWWiad4D8Qa20GmzgH9sH7MH/BNP8AaB/4J3/8EM/j5+yN8BPE9941/as1n4CfH/W/CWo6Jdpo88/xx+IPg3WzbWngme8mtY9FvYdRuLbRvB9zfXVpLDeWGj6lq1zY3896LUA/mX/4Jof8FQ/iN/wSJ/Zd0b4Eyf8ABCj9qDxR8XfB2o+K9W/aE+Kuu6L40+H0esx2mp6rqWpeItTa7/Z+8UalDJo3hVLewdfEGqtouh6Xoq/YbuLSzOzgH9xP/BM79o79mT9sX9k3wF+1d+yv8P8ATvhn4G+OJ1PxF4k8JWvhrQ/CuqaR8RNL1O88P+N7DxRYeG4odF1DxHY6/pt7aXXiW0WQeJbSKx1b7RLFPCkIB9/0AFAH4c/tjfsxftY6f+1vL+0b+zdpMmqS+ItF0GGDV9IuvD7ah4X1vTtAi8LajBqWkeIWMVxaXdhYWd/aX8Vpf26SSyxTRQT20Xnf1z4b+InhVX8K6XAfiRUqxpZZmWIxSwU8JmtaGYUv7QlmuCrYbEZRF1adahiK9ajVoVKuH54Rj71SnVmo/wAA+MfhD46YfxzxHij4O0qM6+c5NhcE8xp5hkOGq5VX/sqOR5lhsZhc/mqNShisJhsPiKGJpUMX7OpJ+7Sr0Kcp874B/wCCZHxx+L/i62+In7WfxLu9SvZJILi60661efxRrlxAj7xpsl7K0dnpdguNh0zSYrCzWPMca+WWRjP/AKR+TZHlVXh7wk4WpZFhXCdOnm2MwtDBxoSknF4vCZRh5VZV8Yl71PGZvi6s4VOWpPDVJRURcK/Q74k4ozyjxb4+8c4jiXG+0hVrZDl2OxWY1cTCDUvqGP4hxlOhDCZfJe5VwOQYGjTlT5qVHG0FLmPi/wD4OKv+CQn7TH7bWn/8E9fGn7F/hnRvFviD9kvx94h0TxH4W1rxXofhvUI/A3jPU/hhqtp4wsZ/EE+nadqkHhLUvh1I+u6PYXD63c2mr28ug6RqAtLm2j/kicpTnOpOUpznKU5zk3Kc5zblOc5PWU5yblKT1lJtvc/v2nCFKnClShGnSpQhSpU6cVGnSpU4qFOnTitI06cIxhCK0jCKitEfamv/APBB39nrxn/wVK+Hn/BV7UfFniPSviZpGheHtS8bfB5tJ0y+8EeJPipoHgSD4faV8RoNXM1vqelahZ+GrWyjvtGeyv7TUPEdjbeJ1vbS7F3a3slH5/8A/Bxz/wAEq/20f23f2mv+Cdfx6/Y6+H2n+PpfgrruvaJ8S57rxl4W8Jv4Etbf4h/D7x74L8USw+I9U0+81fSWmsPFUN+vhy21fUtPlsrMNp7LfQtQB3H/AAWi/wCCPP7Q/wDwVO/bw/4J2p4yudY/4YQ+Hnw78c6V8cpPCPirQtJ8ZeAviBqt6dZv7220rVPtc91b/Ei10nwD4Vj13RdK1z+wLTwxrzai+ktc6Rc3wB8u/t9/8GwHwg+CXgz9lr4qf8Envgf4huP2jfhB+1t8HPG/jq/8YfGvV7+XUvhHodzqGqa7qxs/HPiOHQJbrw74t03whq5tPDdlH4im0uTV4dMtdQRTZgA/Qz9o7/gnf+0z8Vv+Dgb9kn9vOy8DaNe/syfDX9j1/ht4w8TXeuaDPcwfEC61n4xWmoeDrzwfNeya3cWs2i/ESx1KbVJdNk8N3mnLqOkSX0uplLCcAxf+Cdf/AATA/aj/AOCX3/BUX9qG0+A1rot7/wAEoP2otFf4naJ4PXxRYnUPgp8ajqGmva+FdJ8H3Fymq2un6TaHxTo+n69ZW1zpeo/D4eBtF1rU7jxJ4biQgH4z+HP2Hv8Ag40/Ym/a8/4KHfDX9gX4cfC/wz8IP2wv2kfH/wAXPD/7VHiu8+H3iBfD/hnxX4q8T61od94YXVdb13UfDXiMaJ4htdO8U6brfwq8Q6jaaxoKXOg7bdbfVL4A/Zn9in/gkT+2t+zL+yV+32/xl/bI+Iv7U37Yv7Yn7PvxM8Ipc+O/iB4o1LwDovxA1H4ceOdH+H9vpFx4x1XVpNKisvEPi6WLUfEzx2Be0NnBBomhaRpIsrsA8C/Yk/4N+tE+Kn/BEjwf+wl+338ObHwP8fNC1/4reOPAnjXTZNC1zxx+z78Q/GPiXWNX0XV/DPijQ7y8sdb0preTQ4fHPhiz1e68K+MrK2msTMb6y0fXdPAPsj/gmP4X/wCC0/wG/wCCeHx8+Bn7TPhz4beP/wBrn9nyfxT4Y/Y58bfEjxvH4w8IfHTwZoeh6fP8P7b4ieLfD/iDTtbuNPvdSg1Hw5o/iLxHqHh7xvbeH5dHfx5Z22paZNeaiAfAnxn/AGgf+Dkf9vbwT42/Y8tf+Cdfwq/YN0P4n+H9X+Gnxc/aN8WfEpfiS2neCPE1rceH/GknwutdL1u7hW91jQ7zUbGy1G2sPE0traXrvp+v6Ff+R4g08A/oT/4Jo/sM+E/+CdX7H3wr/ZZ8I6nca3aeBNOuJNT1y7CLda14h1i8uNY8RazcpEWgin1bXL/UtSa1t2e109LtNMtJJ7WyhuZgD74oA//Z\" STYLE=\"width:160px;height:120px;\">";
  buf += "</html>\n";

  client.print(buf);
  client.flush();

  if (req.indexOf("mensagem1") != -1){
    mensagemParaSlack("oi, slack");
    Serial.println("Mensagem Enviada!");
  }
  else if (req.indexOf("mensagem2") != -1){
    mensagemParaSlack("tchau, slack");
    Serial.println("Mensagem Enviada!");
  }
  else {
    Serial.println("invalid request");
    client.stop();
  }
}

bool mensagemParaSlack(String msg)
{
  const char* host = "hooks.slack.com";
  Serial.print("Connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClientSecure client;
  const int httpsPort = 443;
  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection failed :-(");
    return false;
  }

  // We now create a URI for the request

  Serial.print("Posting to URL: ");
  Serial.println(slack_hook_url);

  String postData="payload={\"link_names\": 1, \"icon_url\": \"" + slack_icon_url + "\", \"username\": \"" + slack_username + "\", \"text\": \"" + msg + "\"}";

  // This will send the request to the server
  client.print(String("POST ") + slack_hook_url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Connection: close" + "\r\n" +
               "Content-Length:" + postData.length() + "\r\n" +
               "\r\n" + postData);
  Serial.println("Request sent");
  String line = client.readStringUntil('\n');
  Serial.printf("Response code was: ");
  Serial.println(line);
  if (line.startsWith("HTTP/1.1 200 OK")) {
    return true;
  } else {
    return false;
  }
}

void loop(){
  consultaServidor();
}
