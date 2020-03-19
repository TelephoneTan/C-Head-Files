#!python3

import smtplib
import os
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.header import Header

env_dist = os.environ

sender = env_dist.get("mbox", "null")
receivers = ["telephone2021@outlook.com"]
from_name = "whale"
to_name = "Telephone"
subject = "GitHub | Action | nmake"
attachment = "log_github_all.txt"
attachment_name = "test.txt"

mail_host = "smtp.qq.com"
mail_port = 465
login_user = sender
passwd = env_dist.get("boxwd", "null")

# instance with attachment
message = MIMEMultipart()
message['From'] = Header(from_name, 'utf-8')
message['To'] = Header(to_name, 'utf-8')
message['Subject'] = Header(subject, 'utf-8')

with open(attachment, encoding='utf-8') as file_obj:
    contents = file_obj.read()
    message.attach(MIMEText(contents, 'plain', 'utf-8'))

# attachment : current dir's log_github_all.txt
att1 = MIMEText(open(attachment, 'rb').read(), 'base64', 'utf-8')
att1["Content-Type"] = 'application/octet-stream'
# attachment name showed in email
att1["Content-Disposition"] = 'attachment; filename=' + attachment_name
message.attach(att1)

try:
    smtpObj = smtplib.SMTP_SSL(mail_host, mail_port)
    smtpObj.connect(mail_host, mail_port)
    smtpObj.login(login_user, passwd)
    smtpObj.sendmail(sender, receivers, message.as_string())
    print("Email sent")
except smtplib.SMTPException:
    print("Email fail")
