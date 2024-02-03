import os
import time
from datetime import datetime
from math import log

from aiogram import Bot, Dispatcher, executor, types

API_TOKEN = open('.bot_token.txt').read()[:-1]
bot = Bot(token=API_TOKEN)
dp = Dispatcher(bot)
testing_now = False
ready_to_test = False
test_all = False
max_test = 1000
version = '0.7.1'


@dp.message_handler(commands=['klenin'])
async def easter_egg(message: types.Message):
    await message.answer('Семь бед — один ответ: Костыль и велосипед!')


@dp.message_handler(commands=['start'])
async def send_welcome(message: types.Message):
    await message.answer(open('greet.txt').read() + '\nversion ' + version)


@dp.message_handler(commands=['test'])
async def send_welcome(message: types.Message):
    global ready_to_test, testing_now
    if testing_now:
        await message.answer('Another solution is currently being tested!')
        return
    ready_to_test = True
    await message.answer('Well, now send me a .cpp or .txt file.')


@dp.message_handler(commands=['test_all'])
async def send_welcome(message: types.Message):  # rewrite
    global test_all
    test_all = True
    await message.answer('All the documents sent will be handled as solutions\n'
                         'To disable type /test_all again.')


@dp.message_handler(commands=['stop'])
async def stop_testing(message: types.Message):
    global testing_now, ready_to_test
    testing_now = False
    ready_to_test = False


async def check(message, verdict_message):
    global testing_now, ready_to_test
    ready_to_test = False
    testing_now = True
    start_time = time.time()
    last_log_test = 1
    os.chdir('stress')

    for i in range(1, max_test):
        if not testing_now:
            await message.answer('Testing has been suspended by the user.')
            return
        os.system(f'./gen > input.txt ' + str(i))
        os.system(f'./jury < input.txt > answer.txt')
        os.system(f'./package < input.txt > user.txt')
        good_answer = open('answer.txt').read()
        bad_answer = open('user.txt').read()
        if good_answer != bad_answer:
            await message.answer(f'failed at test {i}')
            await message.answer_document(types.InputFile('input.txt'))
            await message.answer_document(types.InputFile('answer.txt'))
            if bad_answer != "":
                await message.answer_document(types.InputFile('user.txt'))
            else:
                await message.answer('Your answer is empty :/')
            testing_now = False
            break
        elif time.time() - start_time >= log(last_log_test):
            start_time = time.time()
            last_log_test = i
            now = datetime.now()
            current_time = now.strftime("%H:%M:%S")
            await verdict_message.edit_text(f'OK {i} | {current_time}')
    await message.answer(str(max_test) +
                         ' tests have been passed, looks like your solution is correct or our generator is weak.')


@dp.message_handler(content_types=['document'])  # actions when receiving a document
async def handle_package(message: types.Message):  # probably to assert only .cpp or .txt?
    global ready_to_test, test_all
    if not test_all and not ready_to_test:
        return
    if testing_now:
        await message.answer('Another solution is currently being tested!')
        return
    file_id = message.document.file_id
    file = await bot.get_file(file_id)
    file_path = file.file_path
    await bot.download_file(file_path=file_path, destination='stress/package.cpp', timeout=120)
    await message.answer('downloaded successfully')
    if os.system('g++ stress/package.cpp -o stress/package') == 0:
        await message.answer('compiled successfully')
    else:
        await message.answer('compilation error :(')
        return
    verdict_message = await message.answer('ща попробуем')
    await check(message, verdict_message)


if __name__ == '__main__':  # start bot
    executor.start_polling(dp, skip_updates=True)


# plans:
    # create git repository
    # documentation
    # assert .cpp or .txt
    # assert other cases
    # to test on a specified test
    # to start from the specified test
    # to add other problems, descriptions for them
    # create different generators
    # add custom generators
    # divide by single-answer and multi-answer tasks

# done:
    # send input / correct / incorrect -- as a file
    # edit message to keep in loop
