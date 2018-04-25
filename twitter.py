import os
import time
import urllib
import hashlib
import hmac

def dict_merge(*ds):
    result = dict()
    for d in ds:
        result.update(d)
    return result

#values are examples from the twitter site at https://developer.twitter.com/en/docs/basics/authentication/guides/creating-a-signature
method = "POST"
base_url = "https://api.twitter.com/1.1/statuses/update.json"
consumer_key = "xvz1evFS4wEEPTGEFPHBog"
consumer_secret = "kAcSOqF21Fu85e7zjz7ZN2U4ZRhfV3WpwPAoE3Z7kBw"
access_token = "370773112-GmHxMAgYyLbNEtIKZeRNFsMKPR9EyMZeS9weJAEb"
access_token_secret = "LswwdoUaIvS8ltyTt5jkRh4J50vUPVVHtR2YPi5kE"
nonce = "kYjzVBB8Y0ZFabxSWbWovY3uYSQ2pTgmZeNu2VS4cg"
timestamp = '1318622958'#str(int(time.time()))

request_params = {'include_entities': 'true'}
content_params = {
        'status': 'Hello Ladies + Gentlemen, a signed OAuth request!'
}
other_params = {
        'oauth_consumer_key': consumer_key,
        'oauth_nonce': nonce,
        'oauth_signature_method': 'HMAC-SHA1',
        'oauth_timestamp': timestamp,
        'oauth_token': access_token,
        'oauth_version': '1.0'
}

all_parameters = dict_merge(request_params, content_params, other_params)
parameter_string = '&'.join(
        urllib.quote(key, safe='')
        + '='
        + urllib.quote(value, safe='')
        for (key, value) in
        sorted(all_parameters.items())
)

signature_base_string = method + "&" + urllib.quote(base_url, safe='') + "&" + urllib.quote(parameter_string, safe='')
signing_key = urllib.quote(consumer_secret, safe='') + "&" + urllib.quote(access_token_secret, safe='')


generated_signature = hmac.new(signing_key, signature_base_string, hashlib.sha1).digest().encode("base64").rstrip('\n')

print("""curl --request {method} --url '{base_url}' --header 'authorization: OAuth oauth_consumer_key="{consumer_key}"
 oauth_nonce="{nonce}", oauth_signature="{generated_signature}", 
 oauth_signature_method="HMAC-SHA1", oauth_timestamp="{timestamp}", 
 oauth_token="{access_token}", oauth_version="1.0"'
""".format(
    method=method,
    base_url=base_url,
    consumer_key=consumer_key,
    nonce=nonce,
    generated_signature=generated_signature,
    timestamp=timestamp,
    access_token=access_token
))
