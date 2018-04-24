import os
import time
import urllib
import hashlib
import hmac

#values are examples from the twitter site at https://developer.twitter.com/en/docs/basics/authentication/guides/creating-a-signature
consumer_key = "xvz1evFS4wEEPTGEFPHBog"
consumer_secret = "kAcSOqF21Fu85e7zjz7ZN2U4ZRhfV3WpwPAoE3Z7kBw"
access_token = "370773112-GmHxMAgYyLbNEtIKZeRNFsMKPR9EyMZeS9weJAEb"
access_token_secret = "LswwdoUaIvS8ltyTth4J50vUPVVHtR2YPi5kE"
nonce = "kYjzVBB8Y0ZFabxSWbWovY3uYSQ2pTgmZeNu2VS4cg"
timestamp = 1318622958#int(time.time())

get_params = {'include_entities': 'true'}
other_params = {
        'oauth_consumer_key': consumer_key,
        'oauth_nonce': nonce,
        'oauth_signature_method': 'HMAC-SHA1',
        'oauth_timestamp': timestamp,
        'oauth_token': access_token,
        'oauth_version': '1.0'
}
parameter_string = urllib.urlencode(dict(get_params, **other_params))
print(parameter_string)
signature_base_string = "GET&" + urllib.quote("http://api.twitter.com/search/tweets.json", safe='') + "&" + urllib.quote(parameter_string, safe='')
signing_key = urllib.quote(consumer_secret, safe='') + "&" + urllib.quote(access_token_secret, safe='')
generated_signature = hmac.new(signing_key, signature_base_string, hashlib.sha1).digest().encode("base64").rstrip('\n')
print(generated_signature)

print("""curl --request GET --url 'https://api.twitter.com/1.1/search/tweets.json?{get_params_encoded}' --header 'authorization: OAuth oauth_consumer_key="{consumer_key}"
 oauth_nonce="{nonce}", oauth_signature="{generated_signature}", 
 oauth_signature_method="HMAC-SHA1", oauth_timestamp="{timestamp}", 
 oauth_token="{access_token}", oauth_version="1.0"'
""".format(
    get_params_encoded=urllib.urlencode(get_params),
    consumer_key=consumer_key,
    nonce=nonce,
    generated_signature=generated_signature,
    timestamp=timestamp,
    access_token=access_token
))
